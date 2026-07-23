#include "graphics/cameras/perspectiveCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{
	PerspectiveCamera::PerspectiveCamera(float fovRad, float nearPlane, float farPlane) :
		Camera{nearPlane, farPlane},
		m_fovRad{fovRad}
	{ }

	void PerspectiveCamera::updateProjectionMatrix()
	{
		m_projectionMatrix = glm::perspective(m_fovRad, m_aspectRatio, m_nearPlane, m_farPlane);
	}
}
