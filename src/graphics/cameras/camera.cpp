#include "graphics/cameras/camera.hpp"

#include "common/transformable.hpp"
#include "graphics/shaderPrograms.hpp"

#include <glm/glm.hpp>

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
		glm::vec3 cameraPosition = getCameraPosition();

		ShaderPrograms::surface->use();
		ShaderPrograms::surface->setUniform("projectionViewMatrix", projectionViewMatrix);
		ShaderPrograms::surface->setUniform("cameraPosition", cameraPosition);

		ShaderPrograms::light->use();
		ShaderPrograms::light->setUniform("projectionViewMatrix", projectionViewMatrix);
		ShaderPrograms::light->setUniform("cameraPosition", cameraPosition);

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

	glm::vec3 Camera::getCameraPosition() const
	{
		glm::vec4 cameraPosition = getCameraMatrix() * glm::vec4{0, 0, 0, 1};
		return glm::vec3{cameraPosition};
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return glm::inverse(getCameraMatrix());
	}
}
