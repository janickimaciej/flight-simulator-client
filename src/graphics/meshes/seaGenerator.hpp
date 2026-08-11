#pragma once

#include "graphics/meshes/vertex.hpp"

#include <vector>

namespace Graphics
{
	class SeaGenerator
	{
	public:
		static std::vector<Vertex> generate();
	};
}
