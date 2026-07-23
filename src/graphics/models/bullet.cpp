#include "graphics/models/bullet.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	const Material tracer{glm::vec3{1, 1, 1}, 1, 1, 1, false};

	Bullet::Bullet()
	{
		auto& proceduralMeshManager = AssetManager<ProceduralMeshName, const Mesh>::instance();

		m_tracer = std::make_unique<Submodel>(*ShaderPrograms::light,
			proceduralMeshManager.get(ProceduralMeshName::bullet), tracer);
	}

	void Bullet::updateShaders()
	{ }

	void Bullet::render() const
	{
		ShaderPrograms::light->use();
		renderLights();
	}

	void Bullet::renderLights() const
	{
		m_tracer->render(getMatrix());
	}
}
