#include "shaderPrograms.hpp"

#include <string>

namespace Graphics::ShaderPrograms
{
	std::string path(const std::string& shaderName);

	std::unique_ptr<const ShaderProgram> hud{};
	std::unique_ptr<const ShaderProgram> light{};
	std::unique_ptr<const ShaderProgram> quad{};
	std::unique_ptr<const ShaderProgram> surface{};
	std::unique_ptr<const ShaderProgram> water{};

	void init()
	{
		hud = std::make_unique<const ShaderProgram>(path("hudVS"), path("hudFS"));
		light = std::make_unique<const ShaderProgram>(path("lightVS"), path("lightFS"));
		quad = std::make_unique<const ShaderProgram>(path("quadVS"), path("quadFS"));
		surface = std::make_unique<const ShaderProgram>(path("surfaceVS"), path("surfaceFS"));
		water = std::make_unique<const ShaderProgram>(path("waterVS"), path("waterFS"));
	}

	std::string path(const std::string& shaderName)
	{
		return "src/graphics/shaders/" + shaderName + ".glsl";
	}
}
