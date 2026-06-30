#include "graphics/worldShading.hpp"

#include "graphics/shaderPrograms.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Graphics
{
	void WorldShading::updateShaders() const
	{
		ShaderPrograms::surface->use();
		ShaderPrograms::surface->setUniform("worldShading.backgroundColor", m_backgroundColor);
		ShaderPrograms::surface->setUniform("worldShading.ambient", m_ambient);
		ShaderPrograms::surface->setUniform("worldShading.fogGradient", m_fogGradient);
		ShaderPrograms::surface->setUniform("worldShading.fogDensity", m_fogDensity);

		ShaderPrograms::light->use();
		ShaderPrograms::light->setUniform("worldShading.backgroundColor", m_backgroundColor);
		ShaderPrograms::light->setUniform("worldShading.fogGradient", m_fogGradient);
		ShaderPrograms::light->setUniform("worldShading.fogDensity", m_fogDensity);

		glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void WorldShading::setBackgroundColor(const glm::vec3& backgroundColor)
	{
		m_backgroundColor = backgroundColor;
	}

	void WorldShading::setAmbient(float ambient)
	{
		m_ambient = ambient;
	}

	void WorldShading::setFogGradient(float fogGradient)
	{
		m_fogGradient = fogGradient;
	}

	void WorldShading::setFogDensity(float fogDensity)
	{
		m_fogDensity = fogDensity;
	}
}
