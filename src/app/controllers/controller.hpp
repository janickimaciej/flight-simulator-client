#pragma once

#include "app/controllers/controllerType.hpp"
#include "physics/playerInput.hpp"

#include <glfw/glfw3.h>

#include <memory>

namespace App
{
	class Controller
	{
	public:
		static std::unique_ptr<Controller> getController(ControllerType type, GLFWwindow* window);

		Controller(GLFWwindow* window);

		Physics::PlayerInput getCurrInput();

	protected:
		GLFWwindow* getWindow() const;
		Physics::PlayerInput& getInput();

	private:
		GLFWwindow* m_window{};
		Physics::PlayerInput m_input{};

		virtual void updateInput() = 0;
	};
}
