#include "app/threads/physicsThread.hpp"

#include "common/sceneInfo.hpp"
#include "physics/playerInput.hpp"

#include <utility>

namespace App
{
	PhysicsThread::PhysicsThread(ExitSignal& exitSignal, GameMode gameMode,
		const Physics::SimulationClock& simulationClock,
		Physics::SimulationBuffer& simulationBuffer, int ownId, Physics::Notification& notification,
		Graphics::RenderingBuffer& renderingBuffer, std::atomic<Physics::PlayerInput>& ownInput,
		UDPCommunication* udpCommunication,
		const std::shared_ptr<std::counting_semaphore<2>>& renderingThreadSemaphore) :
		m_exitSignal{exitSignal},
		m_gameMode{gameMode},
		m_simulationClock{simulationClock},
		m_simulationBuffer{simulationBuffer},
		m_notification{notification},
		m_ownId{ownId},
		m_renderingBuffer{renderingBuffer},
		m_ownInput{ownInput},
		m_udpCommunication{udpCommunication}
	{
		m_thread = std::thread(
			[this, renderingThreadSemaphore]
			{
				this->run(std::move(renderingThreadSemaphore));
			});
	}

	void PhysicsThread::join()
	{
		m_thread.join();
	}

	void PhysicsThread::run(std::shared_ptr<std::counting_semaphore<2>> renderingThreadSemaphore)
	{
		Physics::SimulationStep initialSimulationStep{};

		m_notification.forceGetNotification(initialSimulationStep);

		m_simulationBuffer.writeControlFrame(initialSimulationStep, m_ownId,
			Physics::PlayerInput{});
		m_simulationBuffer.update(initialSimulationStep);

		Common::SceneInfo sceneInfo = m_simulationBuffer.getSceneInfo(initialSimulationStep);
		m_renderingBuffer.update(std::move(sceneInfo));
		renderingThreadSemaphore->release();

		m_newestStateFrameSimulationStep = initialSimulationStep;
		mainLoop(initialSimulationStep);
	}

	void PhysicsThread::mainLoop(const Physics::SimulationStep& initialSimulationStep)
	{
		Physics::SimulationStep simulationStep = initialSimulationStep;
		while (!m_exitSignal.exiting())
		{
			simulationStep = simulationStep.next();
			m_notification.getNotification(simulationStep);
			sleepIfFuture(simulationStep);

			if (simulationStep > m_newestStateFrameSimulationStep)
			{
				Physics::PlayerInput ownInput = m_ownInput;
				m_simulationBuffer.writeOwnInput(simulationStep, ownInput);

				m_simulationBuffer.update(simulationStep);

				Common::SceneInfo sceneInfo = m_simulationBuffer.getSceneInfo(simulationStep);
				m_renderingBuffer.update(std::move(sceneInfo));

				if (m_gameMode == GameMode::multiplayer)
				{
					m_udpCommunication->sendControlFrame(simulationStep, m_ownId, ownInput);
				}

				m_newestStateFrameSimulationStep = simulationStep;
			}
			else
			{
				m_simulationBuffer.update(simulationStep);
			}
		}
	}

	void PhysicsThread::sleepIfFuture(const Physics::SimulationStep& simulationStep)
	{
		Physics::SimulationStep currSimulationStep = m_simulationClock.getTime();
		while (currSimulationStep < simulationStep)
		{
			currSimulationStep = m_simulationClock.getTime();
		}
	}
}
