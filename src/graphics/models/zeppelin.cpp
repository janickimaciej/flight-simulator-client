#include "graphics/models/zeppelin.hpp"

#include "graphics/AssetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderPrograms.hpp"
#include "graphics/submodels/submodel.hpp"

#include <string>

namespace Graphics
{
	const std::string modelName = "zeppelin";

	const std::string fuselagePath = meshPath(modelName, "body");

	const Material canvas{glm::vec3{0.9, 0.9, 0.9}, 0.75, 0.25, 10, false};

	Zeppelin::Zeppelin()
	{
		auto& fileMeshManager = AssetManager<std::string, const Mesh>::instance();

		m_body = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(fuselagePath), canvas);

		static constexpr float zeppelinScale = 57;
		scale(zeppelinScale);
	}

	void Zeppelin::updateShaders()
	{ }

	void Zeppelin::render() const
	{
		ShaderPrograms::surface->use();
		renderSurfaces();
	}

	void Zeppelin::renderSurfaces() const
	{
		m_body->render(getMatrix());
	}
}
