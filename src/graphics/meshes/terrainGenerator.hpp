#pragma once

#include "common/terrains/terrain.hpp"
#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <functional>
#include <vector>

namespace Graphics
{
	class TerrainGenerator
	{
	public:
		static std::vector<Vertex> generate(const Common::Terrains::Terrain& terrain,
			const glm::vec2& size, const glm::vec2& spacing, float waterLevel,
			float waterTransparencyDepth);

	private:
		static std::vector<Vertex> generate(const Common::Terrains::Terrain& terrain,
			const glm::vec2& size, const glm::vec2& spacing,
			const std::function<bool(const std::array<Vertex, 3>&)>& triangleAcceptance);

		static glm::vec3 getPos(int xIndex, int zIndex, const Common::Terrains::Terrain& terrain,
			const glm::vec2& size, const glm::vec2& spacing);
		static glm::vec3 getNormalVector(int xIndex, int zIndex,
			const Common::Terrains::Terrain& terrain, const glm::vec2& size,
			const glm::vec2& spacing);
		static Vertex getVertex(int xIndex, int zIndex, const Common::Terrains::Terrain& terrain,
			const glm::vec2& size, const glm::vec2& spacing, const glm::vec2& texturePos);
	};
}
