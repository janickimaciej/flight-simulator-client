#pragma once

#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/meshes/vertex.hpp"

#include <vector>

namespace Graphics
{
	class MeshGenerator
	{
	public:
		static std::vector<Vertex> generate(ProceduralMeshName name);
	};
}
