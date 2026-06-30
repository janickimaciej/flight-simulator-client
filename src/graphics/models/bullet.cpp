#include "graphics/models/bullet.hpp"

#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	const Material tracer{glm::vec3{1, 1, 1}, 1, 1, 1, false};

	Bullet::Bullet(AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager) :
		m_tracer{*ShaderPrograms::light, proceduralMeshManager.get(ProceduralMeshName::bullet),
			tracer}
	{ }

	void Bullet::updateShaders()
	{ }

	void Bullet::render() const
	{
		ShaderPrograms::light->use();
		renderLights();
	}

	void Bullet::renderLights() const
	{
		m_tracer.render(getMatrix());
	}
}
