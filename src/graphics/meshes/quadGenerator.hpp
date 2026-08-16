#pragma once

#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace Graphics
{
	class QuadGenerator
	{
	public:
		static std::vector<Vertex> generate(const glm::vec2& size, bool inverted);
	};
}
