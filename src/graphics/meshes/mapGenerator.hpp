#pragma once

#include "common/maps/map.hpp"
#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace Graphics
{
	class MapGenerator
	{
	public:
		static std::vector<Vertex> generate(const Common::Maps::Map& map);

	private:
		static glm::vec3 calcPos(float x, float z, const Common::Maps::Map& map);
		static glm::vec3 calcNormalVector(float x, float z, const Common::Maps::Map& map);
	};
}
