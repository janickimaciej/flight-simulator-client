#pragma once

#include <glm/glm.hpp>

namespace Graphics
{
	struct Vertex
	{
		glm::vec3 pos{};
		glm::vec2 texturePos{};
		glm::vec3 normalVector{};
	};
}
