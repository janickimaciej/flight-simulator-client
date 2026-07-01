#pragma once

#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace Graphics
{
	class BulletGenerator
	{
	public:
		static std::vector<Vertex> generate();

	private:
		static void addDoubleSidedTriangle(std::vector<Vertex>& vertices,
			const glm::vec3& vertex1Pos, const glm::vec3& vertex2Pos, const glm::vec3& vertex3Pos);
	};
}
