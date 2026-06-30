#include "shaderPrograms.hpp"

#include <string>

namespace Graphics::ShaderPrograms
{
	std::string path(const std::string& shaderName);

	//std::unique_ptr<const ShaderProgram> surface{};
	//std::unique_ptr<const ShaderProgram> light{};
	//std::unique_ptr<const ShaderProgram> hud{};

	void init()
	{
		//surface = std::make_unique<const ShaderProgram>(path("surfaceVS"), path("surfaceFS"));
		//light = std::make_unique<const ShaderProgram>(path("lightVS"), path("lightFS"));
		//hud = std::make_unique<const ShaderProgram>(path("hudVS"), path("hudFS"));
	}

	std::string path(const std::string& shaderName)
	{
		return "src/graphics/shaders/" + shaderName + ".glsl";
	}
}
