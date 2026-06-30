#include "app/window.hpp"

#include "graphics/shaderPrograms.hpp"

#include <glad/glad.h>

#include <string>

namespace App
{
	Window::Window()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		static const std::string windowTitle = "flight-simulator-client";
		m_windowPtr = glfwCreateWindow(m_initialSize.x, m_initialSize.y, windowTitle.c_str(),
			nullptr, nullptr);
		glfwSetWindowUserPointer(m_windowPtr, this);
		glfwSetInputMode(m_windowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwMakeContextCurrent(m_windowPtr);
		glfwSwapInterval(1);

		glfwSetFramebufferSizeCallback(m_windowPtr, callbackWrapper<&Window::resizeCallback>);
		m_input = std::make_unique<WindowInput>(m_windowPtr);

		gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

		updateViewport();
		Graphics::ShaderPrograms::init();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(m_windowPtr);
	}

	void Window::swapBuffers() const
	{
		glfwSwapBuffers(m_windowPtr);
	}

	void Window::pollEvents() const
	{
		glfwPollEvents();
	}

	float Window::aspectRatio() const
	{
		return static_cast<float>(m_viewportSize.x) / m_viewportSize.y;
	}

	GLFWwindow* Window::getPtr()
	{
		return m_windowPtr;
	}

	Physics::PlayerInput Window::getCurrentInput()
	{
		return m_input->getCurrentInput();
	}

	void Window::setControllerType(ControllerType controllerType)
	{
		m_input->setControllerType(controllerType);
	}

	void Window::resizeCallback(int width, int height)
	{
		if (width == 0 || height == 0)
		{
			return;
		}

		m_viewportSize = {width, height};
		updateViewport();
	}

	void Window::updateViewport() const
	{
		glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
	}
};
