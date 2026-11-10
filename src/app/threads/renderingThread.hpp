#pragma once

#include "app/commandLineArgs.hpp"
#include "app/exitSignal.hpp"
#include "app/window.hpp"
#include "graphics/renderingBuffer.hpp"
#include "physics/playerInput.hpp"

#include <atomic>
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
		std::atomic<Physics::PlayerInput> m_ownInput{};
		std::unique_ptr<Graphics::RenderingBuffer> m_renderingBuffer{};

		void mainLoop();
	};
}
