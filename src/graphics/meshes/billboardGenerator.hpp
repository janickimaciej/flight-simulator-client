#pragma once

#include "graphics/meshes/vertex.hpp"

#include <vector>

namespace Graphics
{
	class BillboardGenerator
	{
	public:
		static std::vector<Vertex> generate(float width, float height);
	};
}
