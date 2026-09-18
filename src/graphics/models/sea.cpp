#include "graphics/models/sea.hpp"

#include "common/config.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/config.hpp"
#include "graphics/material.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	Sea::Sea()
	{
		auto& proceduralMeshManager = AssetManager<ProceduralMeshName, const Mesh>::instance();

		static const Material material{glm::vec3{0.54f, 0.54f, 0.9f}, 0.5f, 0.25f, 20, false};
		std::shared_ptr<const Mesh> waterSurface =
			proceduralMeshManager.get(ProceduralMeshName::sea);
		m_surface = std::make_unique<Submodel>(*ShaderPrograms::surface, waterSurface, material);
		m_blendSurface = std::make_unique<Submodel>(*ShaderPrograms::water, waterSurface, material);
		m_surface->rotatePitch(glm::radians(-90.0f));
		m_blendSurface->rotatePitch(glm::radians(-90.0f));
	}

	void Sea::updateShaders()
	{ }

	void Sea::render() const
	{
		ShaderPrograms::surface->use();
		m_surface->render(getMatrix());
	}

	void Sea::blend() const
	{
		ShaderPrograms::water->use();
		ShaderPrograms::water->setUniform("waterLevel", Common::waterLevel);
		ShaderPrograms::water->setUniform("waterTransparencyDepth", waterTransparencyDepth);
		m_blendSurface->render(getMatrix());
	}
}
