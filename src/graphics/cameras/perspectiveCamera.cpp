#include "graphics/cameras/perspectiveCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{
	PerspectiveCamera::PerspectiveCamera(float nearPlane, float farPlane, float fovYRad) :
		Camera{nearPlane, farPlane},
		m_fovYRad{fovYRad}
	{ }

	void PerspectiveCamera::updateProjectionMatrix()
	{
		m_projectionMatrix = glm::perspective(m_fovYRad, m_aspectRatio, m_nearPlane, m_farPlane);
	}
}
