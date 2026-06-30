#include "app/threads/renderingThread.hpp"

#include "app/controllerType.hpp"
#include "app/exitCode.hpp"
#include "app/exitSignal.hpp"
#include "app/threads/networkThread.hpp"
#include "graphics/time.hpp"
#include "physics/playerInput.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <memory>
#include <semaphore>
#include <string>

namespace App
{
	RenderingThread::RenderingThread(ExitSignal& exitSignal) :
		m_exitSignal{exitSignal}
	{ }

	void RenderingThread::start(const CommandLineArgs& args)
	{
		std::shared_ptr<std::binary_semaphore> semaphore =
			std::make_shared<std::binary_semaphore>(0);
		m_exitSignal.registerOnExit(
			[semaphore] ()
			{
				semaphore->release();
			}
		);

		m_window.setControllerType(args.controllerType);
		NetworkThread networkThread{m_exitSignal, args.gameMode, args.airplaneType,
			args.map, args.serverIPAddress, args.serverNetworkThreadPort,
			args.serverPhysicsThreadPort, args.clientNetworkThreadPort,
			args.clientPhysicsThreadPort, m_ownInput, m_renderingBuffer, semaphore};

		semaphore->acquire();
		if (!m_exitSignal.shouldStop())
		{
			m_renderingBuffer->initialize(args.airplaneType, args.map);
			mainLoop();
		}
		networkThread.join();
	}

	void RenderingThread::mainLoop()
	{
		Graphics::Time::initialize();
		while (!m_exitSignal.shouldStop())
		{
			if (m_window.shouldClose())
			{
				m_exitSignal.exit(ExitCode::ok);
				break;
			}
			Graphics::Time::update();

			processInput();
			m_renderingBuffer->updateAndRenderScene(m_window.aspectRatio());
			m_window.swapBuffers();
			m_window.pollEvents();
		}
	}

	void RenderingThread::processInput()
	{
		Physics::PlayerInput ownInput = m_window.getCurrentInput();
		m_ownInput.setOwnInput(ownInput);
	}
}
