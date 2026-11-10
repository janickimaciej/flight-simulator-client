#include "app/threads/renderingThread.hpp"

#include "app/exitCode.hpp"
#include "app/threads/networkThread.hpp"
#include "graphics/time.hpp"

#include <semaphore>

namespace App
{
	RenderingThread::RenderingThread(ExitSignal& exitSignal) :
		m_exitSignal{exitSignal}
	{ }

	void RenderingThread::start(const CommandLineArgs& args)
	{
		auto semaphore = std::make_shared<std::counting_semaphore<2>>(0);
		m_exitSignal.registerOnExit(
			[semaphore] ()
			{
				semaphore->release();
			}
		);

		m_window.setControllerType(args.controllerType);
		NetworkThread networkThread{m_exitSignal, args, m_ownInput, m_renderingBuffer, semaphore};

		semaphore->acquire();
		if (!m_exitSignal.exiting())
		{
			m_renderingBuffer->initialize(m_window.getViewportSize(), args.airplaneType, args.map);
			Graphics::Time::initialize();
			mainLoop();
		}
		networkThread.join();
	}

	void RenderingThread::mainLoop()
	{
		while (!m_exitSignal.exiting())
		{
			if (m_window.shouldClose())
			{
				m_exitSignal.exit(ExitCode::ok);
				break;
			}
			Graphics::Time::update();

			m_ownInput = m_window.getCurrInput();
			m_renderingBuffer->updateAndRenderScene(m_window.getViewportSize());
			m_window.swapBuffers();
			m_window.pollEvents();
		}
	}
}
