#pragma once

#include "app/controllerType.hpp"
#include "app/windowInput.hpp"
#include "physics/playerInput.hpp"

#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <memory>

namespace App
{
	class Window
	{
	public:
		Window();
		~Window();

		bool shouldClose() const;
		void swapBuffers() const;
		void pollEvents() const;

		float aspectRatio() const;
		GLFWwindow* getPtr();

		Physics::PlayerInput getCurrentInput();
		void setControllerType(ControllerType controllerType);

	private:
		static constexpr glm::ivec2 m_initialSize{1900, 1000};

		GLFWwindow* m_windowPtr{};
		glm::ivec2 m_viewportSize{m_initialSize};
		std::unique_ptr<WindowInput> m_input{};

		void resizeCallback(int width, int height);

		void updateViewport() const;

		template <auto callback, typename... Args>
		static void callbackWrapper(GLFWwindow* windowPtr, Args... args);
	};

	template <auto callback, typename... Args>
	void Window::callbackWrapper(GLFWwindow* windowPtr, Args... args)
	{
		Window* window = static_cast<Window*>(glfwGetWindowUserPointer(windowPtr));
		(window->*callback)(args...);
	}
}
