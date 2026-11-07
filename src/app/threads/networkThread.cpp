#include "app/threads/networkThread.hpp"

#include "app/exitCode.hpp"
#include "app/threads/physicsThread.hpp"
#include "app/udp/udpFrameType.hpp"
#include "physics/airplaneDefinitions.hpp"

#include <utility>

namespace App
{
	NetworkThread::NetworkThread(ExitSignal& exitSignal, const CommandLineArgs& args,
		OwnInput& ownInput, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer,
		const std::shared_ptr<std::counting_semaphore<2>>& renderingThreadSemaphore) :
		m_exitSignal{exitSignal}
	{
		if (args.gameMode == GameMode::multiplayer)
		{
			m_udpCommunication = std::make_unique<UDPCommunication>(args.serverIPAddress,
				args.serverNetworkThreadPort, args.serverPhysicsThreadPort,
				args.clientNetworkThreadPort, args.clientPhysicsThreadPort);
		}
		m_thread = std::thread(
			[this, args, &ownInput, &renderingBuffer, renderingThreadSemaphore]
			{
				this->start(args.gameMode, args.airplaneType, args.map, ownInput, renderingBuffer,
					std::move(renderingThreadSemaphore));
			});
	}

	void NetworkThread::join()
	{
		m_thread.join();
	}

	void NetworkThread::start(GameMode gameMode, Common::AirplaneType airplaneType,
		Common::MapName map, OwnInput& ownInput,
		std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer,
		std::shared_ptr<std::counting_semaphore<2>> renderingThreadSemaphore)
	{
		if (gameMode == GameMode::multiplayer)
		{
			if (!startMultiplayer(airplaneType, map, renderingBuffer))
			{
				m_exitSignal.exit(ExitCode::failedToConnect);
				return;
			}
		}
		else
		{
			startSingleplayer(airplaneType, map, renderingBuffer);
		}
		PhysicsThread physicsThread{m_exitSignal, gameMode, m_simulationClock, *m_simulationBuffer,
			m_ownId, m_notification, *renderingBuffer, ownInput, m_udpCommunication.get(),
			renderingThreadSemaphore};
		if (gameMode == GameMode::multiplayer)
		{
			mainLoopMultiplayer();
		}
		else
		{
			auto semaphore = std::make_shared<std::counting_semaphore<1>>(0);
			m_exitSignal.registerOnExit(
				[semaphore] ()
				{
					semaphore->release();
				}
			);
			semaphore->acquire();
		}
		physicsThread.join();
	}

	bool NetworkThread::startMultiplayer(Common::AirplaneType airplaneType,
		Common::MapName map, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		static constexpr int initReqFrameCount = 10;
		for (int i = 0; i < initReqFrameCount; ++i)
		{
			m_udpCommunication->sendInitReqFrame(airplaneType);
		}

		Physics::Timestamp sendTimestamp{};
		Physics::Timestamp receiveTimestamp{};
		Physics::Timestamp serverTimestamp{};
		if (!m_udpCommunication->receiveInitResFrame(sendTimestamp, receiveTimestamp,
			serverTimestamp, m_ownId))
		{
			m_exitSignal.exit(ExitCode::failedToConnect);
			return false;
		}

		m_udpCommunication->sendKeepaliveFrames();

		m_simulationClock.initializeOffset(sendTimestamp, receiveTimestamp, serverTimestamp);

		m_simulationBuffer = std::make_unique<Physics::SimulationBuffer>(m_ownId, map);
		renderingBuffer = std::make_unique<Graphics::RenderingBuffer>(m_ownId);

		Physics::SimulationStep initialSimulationStep{};
		std::unordered_map<int, Physics::PlayerInfo> playerInfos{};
		if (!m_udpCommunication->receiveStateFrameWithOwnInfo(initialSimulationStep, playerInfos,
			m_ownId))
		{
			m_exitSignal.exit(ExitCode::failedToConnect);
			return false;
		}
		m_simulationBuffer->writeStateFrame(initialSimulationStep, playerInfos);
		m_frameCutoff = initialSimulationStep;

		m_notification.setNotification(initialSimulationStep, true);

		return true;
	}

	void NetworkThread::startSingleplayer(Common::AirplaneType airplaneType,
		Common::MapName map, std::unique_ptr<Graphics::RenderingBuffer>& renderingBuffer)
	{
		static constexpr int ownId = 0;
		m_simulationBuffer = std::make_unique<Physics::SimulationBuffer>(ownId, map);
		renderingBuffer = std::make_unique<Graphics::RenderingBuffer>(ownId);

		Physics::SimulationStep initialSimulationStep = m_simulationClock.getTime();

		Physics::PlayerInfo ownInfo;

		ownInfo.state.hp = Physics::airplaneDefinitions[toSizeT(airplaneType)].initialHP;
		ownInfo.state.state = m_spawner.spawn(airplaneType);
		ownInfo.state.airplaneType = airplaneType;

		std::unordered_map<int, Physics::PlayerInfo> playerInfos;
		playerInfos.insert({ownId, ownInfo});
		m_simulationBuffer->writeStateFrame(initialSimulationStep, std::move(playerInfos));

		m_notification.setNotification(initialSimulationStep, true);
	}

	void NetworkThread::mainLoopMultiplayer()
	{
		while (!m_exitSignal.exiting())
		{
			Physics::Timestamp sendTimestamp{};
			Physics::Timestamp receiveTimestamp{};
			Physics::Timestamp serverTimestamp{};
			UDPFrameType udpFrameType{};
			Physics::SimulationStep simulationStep{};
			int playerId{};
			Physics::PlayerInput playerInput{};
			std::unordered_map<int, Physics::PlayerInfo> playerInfos{};

			if (!m_udpCommunication->receiveControlOrStateFrameWithOwnInfo(sendTimestamp,
				receiveTimestamp, serverTimestamp, udpFrameType, simulationStep, playerId,
				playerInput, playerInfos, m_ownId))
			{
				m_exitSignal.exit(ExitCode::connectionLost);
				return;
			}

			static const Physics::SimulationStep frameAgeCutoffOffset{0u,
				static_cast<unsigned int>(Physics::SimulationStep::stepsPerSecond * 0.9f)};
			Physics::SimulationStep frameAgeCutoff =
				m_simulationClock.getTime() - frameAgeCutoffOffset;
			if (m_frameCutoff < frameAgeCutoff)
			{
				m_frameCutoff = frameAgeCutoff;
			}

			if (simulationStep <= m_frameCutoff)
			{
				continue;
			}

			if (udpFrameType == UDPFrameType::control)
			{
				handleControlFrame(sendTimestamp, receiveTimestamp, serverTimestamp, simulationStep,
					playerId, playerInput);
			}
			else if (udpFrameType == UDPFrameType::state)
			{
				m_udpCommunication->sendKeepaliveFrames();
				handleStateFrame(simulationStep, playerInfos);
			}
		}
	}

	void NetworkThread::handleControlFrame(const Physics::Timestamp& sendTimestamp,
		const Physics::Timestamp& receiveTimestamp, const Physics::Timestamp& serverTimestamp,
		const Physics::SimulationStep& simulationStep, int playerId,
		const Physics::PlayerInput& playerInput)
	{
		if (playerId == m_ownId)
		{
			m_simulationClock.updateOffset(sendTimestamp, receiveTimestamp,
				serverTimestamp);
		}
		else
		{
			m_simulationBuffer->writeControlFrame(simulationStep, playerId, playerInput);
			m_notification.setNotification(simulationStep, false);
		}
	}

	void NetworkThread::handleStateFrame(const Physics::SimulationStep& simulationStep,
		const std::unordered_map<int, Physics::PlayerInfo>& playerInfos)
	{
		m_frameCutoff = simulationStep;

		m_simulationBuffer->writeStateFrame(simulationStep, playerInfos);
		m_notification.setNotification(simulationStep, true);
	}
}
