#include "graphics/models/islandLand.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/material.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderPrograms.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	IslandLand::IslandLand()
	{
		auto& proceduralMeshManager = AssetManager<ProceduralMeshName, const Mesh>::instance();
		auto& textureManager = AssetManager<std::string, const Texture>::instance();

		static const Material material{glm::vec3{1, 1, 1}, 0.75f, 0, 10, false};
		static const std::string modelName = "island";
		static const std::string grassPath = texturePath(modelName, "grass");
		m_surface = std::make_unique<Submodel>(*ShaderPrograms::surface,
			proceduralMeshManager.get(ProceduralMeshName::islandLand), material,
			textureManager.get(Texture::getId(grassPath)));
	}

	void IslandLand::updateShaders()
	{ }

	void IslandLand::render() const
	{
		ShaderPrograms::surface->use();
		m_surface->render(getMatrix());
	}
}
