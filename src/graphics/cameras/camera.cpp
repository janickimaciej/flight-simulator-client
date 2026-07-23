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
		glm::mat4 projectionViewMatrix = m_projectionMatrix * getViewMatrix();
		glm::vec3 cameraPos = getCameraPos();

		ShaderPrograms::surface->use();
		ShaderPrograms::surface->setUniform("projectionViewMatrix", projectionViewMatrix);
		ShaderPrograms::surface->setUniform("cameraPos", cameraPos);

		ShaderPrograms::light->use();
		ShaderPrograms::light->setUniform("projectionViewMatrix", projectionViewMatrix);
		ShaderPrograms::light->setUniform("cameraPos", cameraPos);

		ShaderPrograms::hud->use();
		ShaderPrograms::hud->setUniform("projectionViewMatrix", projectionViewMatrix);
	}

	Camera::Camera(float nearPlane, float farPlane) :
		m_nearPlane{nearPlane},
		m_farPlane{farPlane}
	{ }

	glm::mat4 Camera::getCameraMatrix() const
	{
		return getMatrix();
	}

	glm::vec3 Camera::getCameraPos() const
	{
		glm::vec4 cameraPos = getCameraMatrix() * glm::vec4{0, 0, 0, 1};
		return glm::vec3{cameraPos};
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return glm::inverse(getCameraMatrix());
	}
}
