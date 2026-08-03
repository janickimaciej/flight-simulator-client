#include "app/controllers/gamepad.hpp"

namespace App
{
	Gamepad::Gamepad(GLFWwindow* window) :
		Controller{window}
	{ }

	bool Gamepad::m_wasDecreaseThrustPressed = false;

	bool Gamepad::m_wasIncreaseThrustPressed = false;

	void Gamepad::updateInput()
	{
		Physics::PlayerInput& input = getInput();

		GLFWgamepadstate gamepad{};
		glfwGetGamepadState(GLFW_JOYSTICK_1, &gamepad);
		
		static constexpr float pitchThreshold = 0.2f;
		float axis1 = gamepad.axes[1];
		if (axis1 > -pitchThreshold && axis1 < pitchThreshold) axis1 = 0;
		input.pitch = axis1;

		static constexpr float yawThreshold = 0.3f;
		float axis4 = gamepad.axes[4];
		if (axis4 < -1 + yawThreshold) axis4 = -1;
		float axis5 = gamepad.axes[5];
		if (axis5 < -1 + yawThreshold) axis5 = -1;
		input.yaw = (axis5 - axis4) / 2;
		
		static constexpr float rollThreshold = 0.1f;
		float axis0 = gamepad.axes[0];
		if (axis0 > -rollThreshold && axis0 < rollThreshold) axis0 = 0;
		input.roll = axis0;

		if (gamepad.buttons[0] == GLFW_PRESS)
		{
			if (!m_wasDecreaseThrustPressed)
			{
				input.thrust -= 0.1f;
			}
			m_wasDecreaseThrustPressed = true;
		}
		else
		{
			m_wasDecreaseThrustPressed = false;
		}
		if (input.thrust < 0)
		{
			input.thrust = 0;
		}

		if (gamepad.buttons[3] == GLFW_PRESS)
		{
			if (!m_wasIncreaseThrustPressed)
			{
				input.thrust += 0.1f;
			}
			m_wasIncreaseThrustPressed = true;
		}
		else
		{
			m_wasIncreaseThrustPressed = false;
		}
		if (input.thrust > 1)
		{
			input.thrust = 1;
		}

		if (gamepad.buttons[2] == GLFW_PRESS)
		{
			input.thrust = 0;
		}

		if (gamepad.buttons[1] == GLFW_PRESS)
		{
			input.thrust = 1;
		}

		input.trigger = gamepad.buttons[5] == GLFW_PRESS;
	}
}
