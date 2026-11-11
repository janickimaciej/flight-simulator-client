#pragma once

#include "app/exitSignal.hpp"
#include "app/gameMode.hpp"
#include "app/udp/udpCommunication.hpp"
#include "graphics/renderingBuffer.hpp"
#include "physics/notification.hpp"
#include "physics/playerInput.hpp"
#include "physics/simulationBuffer.hpp"
#include "physics/simulationClock.hpp"
#include "physics/simulationStep.hpp"

#include <atomic>
#include <memory>
#include <semaphore>
#include <thread>

namespace App
{
	class PhysicsThread
	{
	public:
		PhysicsThread(ExitSignal& exitSignal, GameMode gameMode,
			const Physics::SimulationClock& simulationClock,
			Physics::SimulationBuffer& simulationBuffer, int ownId,
			Physics::Notification& notification, Graphics::RenderingBuffer& renderingBuffer,
			std::atomic<Physics::PlayerInput>& ownInput, UDPCommunication* udpCommunication,
			const std::shared_ptr<std::counting_semaphore<2>>& renderingThreadSemaphore);

		void join();

	private:
		std::thread m_thread{};
		ExitSignal& m_exitSignal;

		GameMode m_gameMode;

		const Physics::SimulationClock& m_simulationClock;
		Physics::SimulationBuffer& m_simulationBuffer;
		Physics::Notification& m_notification;
		int m_ownId{};

		Graphics::RenderingBuffer& m_renderingBuffer;
		std::atomic<Physics::PlayerInput>& m_ownInput;
		Physics::SimulationStep m_newestStateFrameSimulationStep{};

		UDPCommunication* m_udpCommunication;

		void run(std::shared_ptr<std::counting_semaphore<2>> renderingThreadSemaphore);
		void mainLoop(const Physics::SimulationStep& initialSimulationStep);
		void sleepIfFuture(const Physics::SimulationStep& simulationStep);
	};
}
