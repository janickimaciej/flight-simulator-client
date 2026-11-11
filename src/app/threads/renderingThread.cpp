#include "app/threads/renderingThread.hpp"

#include "app/exitCode.hpp"
#include "app/threads/networkThread.hpp"
#include "common/sceneInfo.hpp"
#include "graphics/time.hpp"

#include <semaphore>

namespace App
{
	RenderingThread::RenderingThread(ExitSignal& exitSignal) :
		m_exitSignal{exitSignal}
	{ }

	void RenderingThread::run(const CommandLineArgs& args)
	{
		auto semaphore = std::make_shared<std::counting_semaphore<2>>(0);
		m_exitSignal.registerOnExit(
			[semaphore] ()
			{
				semaphore->release();
			}
		);

		m_window.setControllerType(args.controllerType);
		int ownId{};
		NetworkThread networkThread{m_exitSignal, args, ownId, m_ownInput, m_renderingBuffer,
			semaphore};

		semaphore->acquire();
		if (!m_exitSignal.exiting())
		{
			m_scene = std::make_unique<Graphics::Scene>(
				m_window.getViewportSize(), ownId, args.airplaneType, args.map);
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

			const Common::SceneInfo& sceneInfo = m_renderingBuffer.getLastUpdated();
			m_scene->updateAndRender(sceneInfo, m_window.getViewportSize());

			m_window.swapBuffers();
			m_window.pollEvents();
		}
	}
}
