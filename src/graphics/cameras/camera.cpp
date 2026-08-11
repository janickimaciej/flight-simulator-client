#include "graphics/cameras/camera.hpp"

#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	void Camera::use(float aspectRatio)
	{
		if (aspectRatio != m_aspectRatio)
		{
			m_aspectRatio = aspectRatio;
			updateProjectionMatrix();
		}
		updateShaders();
	}

	Camera::Camera(float nearPlane, float farPlane) :
		m_nearPlane{nearPlane},
		m_farPlane{farPlane}
	{ }

	glm::mat4 Camera::getViewMatrixInverse() const
	{
		return getMatrix();
	}

	glm::vec3 Camera::getWorldPos() const
	{
		glm::vec4 worldPos = getViewMatrixInverse() * glm::vec4{0, 0, 0, 1};
		return glm::vec3{worldPos};
	}

	void Camera::updateShaders() const
	{
		glm::mat4 projectionViewMatrix = m_projectionMatrix * glm::inverse(getViewMatrixInverse());
		glm::vec3 worldPos = getWorldPos();

		ShaderPrograms::surface->use();
		ShaderPrograms::surface->setUniform("projectionViewMatrix", projectionViewMatrix);
		ShaderPrograms::surface->setUniform("cameraPos", worldPos);

		ShaderPrograms::sea->use();
		ShaderPrograms::sea->setUniform("projectionViewMatrix", projectionViewMatrix);
		ShaderPrograms::sea->setUniform("cameraPos", worldPos);

		ShaderPrograms::light->use();
		ShaderPrograms::light->setUniform("projectionViewMatrix", projectionViewMatrix);
		ShaderPrograms::light->setUniform("cameraPos", worldPos);

		ShaderPrograms::hud->use();
		ShaderPrograms::hud->setUniform("projectionViewMatrix", projectionViewMatrix);
	}
}
