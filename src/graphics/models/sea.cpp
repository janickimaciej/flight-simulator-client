#include "graphics/models/sea.hpp"

#include "graphics/material.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	Sea::Sea()
	{
		static const Material material{glm::vec3{0.54f, 0.54f, 0.9f}, 0.5f, 0.25f, 20, false};
		m_surface = std::make_unique<Submodel>(*ShaderPrograms::sea,
			std::make_shared<Mesh>(ProceduralMeshName::sea, true), material);
	}

	void Sea::updateShaders()
	{ }

	void Sea::render() const
	{
		ShaderPrograms::sea->use();
		m_surface->render(getMatrix());
	}
}
