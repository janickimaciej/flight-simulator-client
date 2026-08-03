#pragma once

#include "app/controllers/controller.hpp"
#include "physics/playerInput.hpp"

#include <glfw/glfw3.h>

namespace App
{
	class Keyboard : public Controller
	{
	public:
		Keyboard(GLFWwindow* window);

	private:
		static bool m_wasDecreaseThrustPressed;
		static bool m_wasIncreaseThrustPressed;

		virtual void updateInput() override;
		bool isKeyPressed(int key) const;
	};
}
