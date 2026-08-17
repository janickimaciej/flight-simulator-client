#include "app/controllers/gamepad.hpp"

namespace App
{
	namespace
	{
		float thresholdLeftMapping(float value, float threshold)
		{
			if (value < -1 + threshold)
			{
				return -1;
			}
			return (2 * value - threshold) / (2 - threshold);
		}

		float thresholdMiddleMapping(float value, float threshold)
		{
			if (value < -threshold)
			{
				return (value + threshold) / (1 - threshold);
			}
			if (value < threshold)
			{
				return 0;
			}
			return (value - threshold) / (1 - threshold);
		}
	};

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
		input.pitch = thresholdMiddleMapping(gamepad.axes[1], pitchThreshold);

		static constexpr float yawThreshold = 0.3f;
		float yawNegative = thresholdLeftMapping(gamepad.axes[4], yawThreshold);
		float yawPositive = thresholdLeftMapping(gamepad.axes[5], yawThreshold);
		input.yaw = (yawPositive - yawNegative) / 2;

		static constexpr float rollThreshold = 0.1f;
		input.roll = thresholdMiddleMapping(gamepad.axes[0], rollThreshold);

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
