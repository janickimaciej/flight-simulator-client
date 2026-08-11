#include "graphics/screenQuad.hpp"

#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	void ScreenQuad::render() const
	{
		ShaderPrograms::quad->use();
		m_mesh.render();
	}
}
