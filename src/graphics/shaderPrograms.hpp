#pragma once

#include "graphics/shaderProgram.hpp"

#include <memory>

namespace Graphics::ShaderPrograms
{
	void init();

	extern std::unique_ptr<const ShaderProgram> surface;
	extern std::unique_ptr<const ShaderProgram> sea;
	extern std::unique_ptr<const ShaderProgram> light;
	extern std::unique_ptr<const ShaderProgram> hud;
	extern std::unique_ptr<const ShaderProgram> quad;
}
