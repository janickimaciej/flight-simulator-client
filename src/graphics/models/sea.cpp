#include "graphics/models/sea.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/material.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	Sea::Sea()
	{
		auto& proceduralMeshManager = AssetManager<ProceduralMeshName, const Mesh>::instance();

		static const Material material{glm::vec3{0.54f, 0.54f, 0.9f}, 0.5f, 0.25f, 20, false};
		m_surface = std::make_unique<Submodel>(*ShaderPrograms::water,
			proceduralMeshManager.get(ProceduralMeshName::sea), material);
		m_surface->rotatePitch(glm::radians(-90.0f));
	}

	void Sea::updateShaders()
	{ }

	void Sea::render() const
	{
		ShaderPrograms::water->use();
		ShaderPrograms::water->setUniform("waterLevel", 0.0f);
		m_surface->render(getMatrix());
	}
}
