#pragma once

#include "app/commandLineArgs.hpp"
#include "app/exitSignal.hpp"
#include "app/gameMode.hpp"
#include "app/udp/udpCommunication.hpp"
#include "common/airplaneType.hpp"
#include "common/mapName.hpp"
#include "graphics/renderingBuffer.hpp"
#include "physics/notification.hpp"
#include "physics/playerInfo.hpp"
#include "physics/playerInput.hpp"
#include "physics/simulationBuffer.hpp"
#include "physics/simulationClock.hpp"
#include "physics/spawner.hpp"
#include "physics/simulationStep.hpp"
#include "physics/timestamp.hpp"

#include <atomic>
#include <memory>
#include <semaphore>
#include <string>
#include <thread>
#include <unordered_map>

namespace App
{
	class NetworkThread
	{
	public:
		NetworkThread(ExitSignal& exitSignal, const CommandLineArgs& args,
			int& ownId, std::atomic<Physics::PlayerInput>& ownInput,
			Graphics::RenderingBuffer& renderingBuffer,
			const std::shared_ptr<std::counting_semaphore<2>>& renderingThreadSemaphore);

		void join();

	private:
		std::thread m_thread{};
		ExitSignal& m_exitSignal;

		Physics::SimulationClock m_simulationClock{};
		std::unique_ptr<Physics::SimulationBuffer> m_simulationBuffer{};
		int m_ownId{};
		Physics::Spawner m_spawner{};

		Physics::Notification m_notification{m_simulationClock};
		Physics::SimulationStep m_frameCutoff{};
		std::unique_ptr<UDPCommunication> m_udpCommunication;

		void run(GameMode gameMode, Common::AirplaneType airplaneType, Common::MapName map,
			int& ownId, std::atomic<Physics::PlayerInput>& ownInput,
			Graphics::RenderingBuffer& renderingBuffer,
			std::shared_ptr<std::counting_semaphore<2>> renderingThreadSemaphore);
		bool startMultiplayer(Common::AirplaneType airplaneType, Common::MapName map);
		void startSingleplayer(Common::AirplaneType airplaneType, Common::MapName map);
		void mainLoopMultiplayer();

		void handleControlFrame(const Physics::Timestamp& sendTimestamp,
			const Physics::Timestamp& receiveTimestamp, const Physics::Timestamp& serverTimestamp,
			const Physics::SimulationStep& simulationStep, int playerId,
			const Physics::PlayerInput& playerInput);
		void handleStateFrame(const Physics::SimulationStep& simulationStep,
			const std::unordered_map<int, Physics::PlayerInfo>& playerInfos);
	};
}
