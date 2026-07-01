#pragma once

#include "app/controllerType.hpp"
#include "physics/playerInput.hpp"

#include <glfw/glfw3.h>

namespace App
{
	class WindowInput
	{
	public:
		WindowInput(GLFWwindow* window);
		Physics::PlayerInput getCurrInput();
		void setControllerType(ControllerType controllerType);

	private:
		Physics::PlayerInput m_ownInput{};
		GLFWwindow* m_windowPtr;
		ControllerType m_controllerType{};

		void updateCurrInputKeyboard();
		void updateCurrInputGamepad();

		bool isKeyPressed(int key);
	};
}
