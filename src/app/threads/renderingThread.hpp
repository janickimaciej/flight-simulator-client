#pragma once

#include "app/commandLineArgs.hpp"
#include "app/controllerType.hpp"
#include "app/exitSignal.hpp"
#include "app/ownInput.hpp"
#include "app/windowInput.hpp"
#include "app/windowPayload.hpp"
#include "graphics/renderingBuffer.hpp"

#include <glfw/glfw3.h>

#include <memory>

namespace App
{
	class RenderingThread
	{
	public:
		RenderingThread(ExitSignal& exitSignal, ControllerType controllerType);
		void start(const CommandLineArgs& args);

	private:
		ExitSignal& m_exitSignal;

		GLFWwindow* m_window{};
		WindowPayload m_windowPayload{};
		std::unique_ptr<Graphics::RenderingBuffer> m_renderingBuffer{};

		WindowInput m_windowInput;
		OwnInput m_ownInput{};

		void mainLoop();
		void initializeWindow();
		static void resizeWindow(GLFWwindow* window, int width, int height);
		void processInput();
	};
}
