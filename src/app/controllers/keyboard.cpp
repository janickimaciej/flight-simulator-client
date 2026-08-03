#include "app/controllers/keyboard.hpp"

namespace App
{
	Keyboard::Keyboard(GLFWwindow* window) :
		Controller{window}
	{ }

	bool Keyboard::m_wasDecreaseThrustPressed = false;

	bool Keyboard::m_wasIncreaseThrustPressed = false;

	void Keyboard::updateInput()
	{
		Physics::PlayerInput& input = getInput();

		int ctrlPitchNegative = isKeyPressed(GLFW_KEY_UP);
		int ctrlPitchPositive = isKeyPressed(GLFW_KEY_DOWN);
		input.pitch = static_cast<float>(ctrlPitchPositive - ctrlPitchNegative);

		int ctrlYawNegative = isKeyPressed(GLFW_KEY_A);
		int ctrlYawPositive = isKeyPressed(GLFW_KEY_D);
		input.yaw = static_cast<float>(ctrlYawPositive - ctrlYawNegative);

		int ctrlRollNegative = isKeyPressed(GLFW_KEY_LEFT);
		int ctrlRollPositive = isKeyPressed(GLFW_KEY_RIGHT);
		input.roll = static_cast<float>(ctrlRollPositive - ctrlRollNegative);

		if (isKeyPressed(GLFW_KEY_S))
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

		if (isKeyPressed(GLFW_KEY_W))
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

		if (isKeyPressed(GLFW_KEY_Q))
		{
			input.thrust = 0;
		}

		if (isKeyPressed(GLFW_KEY_E))
		{
			input.thrust = 1;
		}

		input.trigger = isKeyPressed(GLFW_KEY_SPACE);
	}

	bool Keyboard::isKeyPressed(int key) const
	{
		return glfwGetKey(getWindow(), key) == GLFW_PRESS;
	}
}
