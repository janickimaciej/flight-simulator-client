#include "app/threads/renderingThread.hpp"

#include "app/controllerType.hpp"
#include "app/exitCode.hpp"
#include "app/exitSignal.hpp"
#include "app/threads/networkThread.hpp"
#include "app/windowPayload.hpp"
#include "graphics/time.hpp"
#include "physics/playerInput.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <memory>
#include <semaphore>
#include <string>

namespace App
{
	RenderingThread::RenderingThread(ExitSignal& exitSignal, ControllerType controllerType) :
		m_exitSignal{exitSignal},
		m_windowInput{m_window, controllerType}
	{ }

	void RenderingThread::start(const CommandLineArgs& args)
	{
		std::shared_ptr<std::binary_semaphore> semaphore =
			std::make_shared<std::binary_semaphore>(0);
		m_exitSignal.registerOnExit([semaphore] ()
			{
				semaphore->release();
			});

		NetworkThread networkThread{m_exitSignal, args.gameMode, args.airplaneTypeName,
			args.mapName, args.serverIPAddress, args.serverNetworkThreadPort,
			args.serverPhysicsThreadPort, args.clientNetworkThreadPort,
			args.clientPhysicsThreadPort, m_ownInput, m_renderingBuffer, semaphore};

		initializeWindow();
		semaphore->acquire();
		if (!m_exitSignal.shouldStop())
		{
			m_renderingBuffer->initialize(args.airplaneTypeName, args.mapName);
			mainLoop();
			glfwTerminate();
		}
		networkThread.join();
	}

	void RenderingThread::mainLoop()
	{
		Graphics::Time::initialize();
		while (!m_exitSignal.shouldStop())
		{
			if (glfwWindowShouldClose(m_window))
			{
				m_exitSignal.exit(ExitCode::ok);
				break;
			}
			Graphics::Time::update();

			processInput();
			m_renderingBuffer->updateAndRenderScene(m_windowPayload.aspectRatio);
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}
	}

	void RenderingThread::initializeWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		const int initialWindowWidth = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
		const int initialWindowHeight = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
		m_windowPayload.aspectRatio = static_cast<float>(initialWindowWidth) / initialWindowHeight;
		const std::string windowTitle = "flight-simulator-client";
		m_window = glfwCreateWindow(initialWindowWidth, initialWindowHeight, windowTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
		glfwSetWindowUserPointer(m_window, &m_windowPayload);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);

		glfwSetFramebufferSizeCallback(m_window, resizeWindow);

		gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
	}

	void RenderingThread::resizeWindow(GLFWwindow* window, int width, int height)
	{
		if (width == 0 || height == 0)
		{
			return;
		}
		WindowPayload* windowPayload =
			static_cast<WindowPayload*>(glfwGetWindowUserPointer(window));
		windowPayload->aspectRatio = static_cast<float>(width) / height;
		glViewport(0, 0, width, height);
	}

	void RenderingThread::processInput()
	{
		const Physics::PlayerInput& ownInput = m_windowInput.getCurrentInput();
		m_ownInput.setOwnInput(ownInput);
	}
}
