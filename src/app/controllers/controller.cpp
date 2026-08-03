#include "app/controllers/controller.hpp"

#include "app/controllers/gamepad.hpp"
#include "app/controllers/keyboard.hpp"

namespace App
{
	std::unique_ptr<Controller> Controller::getController(ControllerType type, GLFWwindow* window)
	{
		switch (type)
		{
			case ControllerType::keyboard:
				return std::make_unique<Keyboard>(window);

			case ControllerType::gamepad:
				return std::make_unique<Gamepad>(window);
		}
		return {};
	}

	Controller::Controller(GLFWwindow* window) :
		m_window{window}
	{ }

	Physics::PlayerInput Controller::getCurrInput()
	{
		updateInput();
		return m_input;
	}

	GLFWwindow* Controller::getWindow() const
	{
		return m_window;
	}

	Physics::PlayerInput& Controller::getInput()
	{
		return m_input;
	}
}
