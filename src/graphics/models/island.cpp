#include "graphics/models/island.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderPrograms.hpp"
#include "graphics/texture.hpp"

namespace Graphics
{
	const std::string modelName = "island";

	const std::string grassPath = texturePath(modelName, "grass");

	const Material ground{glm::vec3{1, 1, 1}, 0.75, 0, 10, false};

	Island::Island(AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager) :
		m_ground{*ShaderPrograms::surface, proceduralMeshManager.get(ProceduralMeshName::island),
			ground, textureManager.get(grassPath)}
	{ }

	void Island::updateShaders()
	{ }

	void Island::render() const
	{
		ShaderPrograms::surface->use();
		renderSurfaces();
	}

	void Island::renderSurfaces() const
	{
		m_ground.render(getMatrix());
	}
}
