#include "app/windowInput.hpp"

#include "physics/playerInput.hpp"

#include <glfw/glfw3.h>

namespace App
{
	WindowInput::WindowInput(GLFWwindow* windowPtr) :
		m_windowPtr{windowPtr}
	{ }

	Physics::PlayerInput WindowInput::getCurrentInput()
	{
		switch (m_controllerType)
		{
			case ControllerType::keyboard:
				updateCurrentInputKeyboard();
				break;

			case ControllerType::gamepad:
				updateCurrentInputGamepad();
				break;
		}

		return m_ownInput;
	}

	void WindowInput::setControllerType(ControllerType controllerType)
	{
		m_controllerType = controllerType;
	}

	void WindowInput::updateCurrentInputKeyboard()
	{
		int ctrlPitchNegative = isKeyPressed(GLFW_KEY_UP);
		int ctrlPitchPositive = isKeyPressed(GLFW_KEY_DOWN);
		m_ownInput.pitch = static_cast<float>(ctrlPitchPositive - ctrlPitchNegative);

		int ctrlYawNegative = isKeyPressed(GLFW_KEY_A);
		int ctrlYawPositive = isKeyPressed(GLFW_KEY_D);
		m_ownInput.yaw = static_cast<float>(ctrlYawPositive - ctrlYawNegative);

		int ctrlRollNegative = isKeyPressed(GLFW_KEY_LEFT);
		int ctrlRollPositive = isKeyPressed(GLFW_KEY_RIGHT);
		m_ownInput.roll = static_cast<float>(ctrlRollPositive - ctrlRollNegative);

		static bool wasDecreaseThrustPressed = false;
		if (isKeyPressed(GLFW_KEY_S))
		{
			if (!wasDecreaseThrustPressed)
			{
				m_ownInput.thrust -= 0.1f;
			}
			wasDecreaseThrustPressed = true;
		}
		else
		{
			wasDecreaseThrustPressed = false;
		}
		if (m_ownInput.thrust < 0)
		{
			m_ownInput.thrust = 0;
		}

		static bool wasIncreaseThrustPressed = false;
		if (isKeyPressed(GLFW_KEY_W))
		{
			if (!wasIncreaseThrustPressed)
			{
				m_ownInput.thrust += 0.1f;
			}
			wasIncreaseThrustPressed = true;
		}
		else
		{
			wasIncreaseThrustPressed = false;
		}
		if (m_ownInput.thrust > 1)
		{
			m_ownInput.thrust = 1;
		}

		if (isKeyPressed(GLFW_KEY_Q))
		{
			m_ownInput.thrust = 0;
		}

		if (isKeyPressed(GLFW_KEY_E))
		{
			m_ownInput.thrust = 1;
		}

		m_ownInput.trigger = isKeyPressed(GLFW_KEY_SPACE);
	}

	void WindowInput::updateCurrentInputGamepad()
	{
		GLFWgamepadstate gamepad{};
		glfwGetGamepadState(GLFW_JOYSTICK_1, &gamepad);

		m_ownInput.pitch = gamepad.axes[1];

		m_ownInput.yaw = (gamepad.axes[5] - gamepad.axes[4]) / 2;

		m_ownInput.roll = gamepad.axes[0];

		static bool wasDecreaseThrustPressed = false;
		if (gamepad.buttons[0] == GLFW_PRESS)
		{
			if (!wasDecreaseThrustPressed)
			{
				m_ownInput.thrust -= 0.1f;
			}
			wasDecreaseThrustPressed = true;
		}
		else
		{
			wasDecreaseThrustPressed = false;
		}
		if (m_ownInput.thrust < 0)
		{
			m_ownInput.thrust = 0;
		}

		static bool wasIncreaseThrustPressed = false;
		if (gamepad.buttons[3] == GLFW_PRESS)
		{
			if (!wasIncreaseThrustPressed)
			{
				m_ownInput.thrust += 0.1f;
			}
			wasIncreaseThrustPressed = true;
		}
		else
		{
			wasIncreaseThrustPressed = false;
		}
		if (m_ownInput.thrust > 1)
		{
			m_ownInput.thrust = 1;
		}

		if (gamepad.buttons[2] == GLFW_PRESS)
		{
			m_ownInput.thrust = 0;
		}

		if (gamepad.buttons[1] == GLFW_PRESS)
		{
			m_ownInput.thrust = 1;
		}

		m_ownInput.trigger = gamepad.buttons[5] == GLFW_PRESS;
	}

	bool WindowInput::isKeyPressed(int key)
	{
		return glfwGetKey(m_windowPtr, key) == GLFW_PRESS;
	}
}
