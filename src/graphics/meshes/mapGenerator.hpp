#pragma once

#include "common/terrains/terrain.hpp"
#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace Graphics
{
	class MapGenerator
	{
	public:
		static std::vector<Vertex> generate(const Common::Terrains::Terrain& terrain,
			const glm::vec2& size, const glm::vec2& spacing);

	private:
		static glm::vec3 calcPos(int xIndex, int zIndex, const Common::Terrains::Terrain& terrain,
			const glm::vec2& size, const glm::vec2& spacing);
		static glm::vec3 calcNormalVector(int xIndex, int zIndex,
			const Common::Terrains::Terrain& terrain, const glm::vec2& size,
			const glm::vec2& spacing);
	};
}
