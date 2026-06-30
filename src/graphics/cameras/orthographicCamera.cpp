#include "graphics/cameras/orthographicCamera.hpp"

namespace Graphics
{
	OrthographicCamera::OrthographicCamera(float width, float nearPlane, float farPlane) :
		Camera{nearPlane, farPlane},
		m_width{width}
	{ }

	void OrthographicCamera::updateProjectionMatrix()
	{
		float height = m_width / m_aspectRatio;
		m_projectionMatrix = glm::ortho(-m_width / 2, m_width / 2, -height / 2, height / 2,
			m_nearPlane, m_farPlane);
	}
}
