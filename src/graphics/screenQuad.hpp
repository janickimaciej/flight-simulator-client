#pragma once

#include "graphics/meshes/mesh.hpp"

namespace Graphics
{
	class ScreenQuad
	{
	public:
		void render() const;

	private:
		Mesh m_mesh{ProceduralMeshName::screenQuad};
	};
}
