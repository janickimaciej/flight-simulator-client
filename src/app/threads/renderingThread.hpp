#pragma once

#include "app/commandLineArgs.hpp"
#include "app/controllerType.hpp"
#include "app/exitSignal.hpp"
#include "app/ownInput.hpp"
#include "app/window.hpp"
#include "graphics/renderingBuffer.hpp"

#include <glfw/glfw3.h>

#include <memory>

namespace App
{
	class RenderingThread
	{
	public:
		RenderingThread(ExitSignal& exitSignal);

		void start(const CommandLineArgs& args);

	private:
		ExitSignal& m_exitSignal;

		Window m_window{};
		OwnInput m_ownInput{};
		std::unique_ptr<Graphics::RenderingBuffer> m_renderingBuffer{};

		void mainLoop();
		void processInput();
	};
}
