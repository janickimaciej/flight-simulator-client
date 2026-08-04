#include "graphics/cameras/orthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{
	OrthographicCamera::OrthographicCamera(float nearPlane, float farPlane, float viewHeight) :
		Camera{nearPlane, farPlane},
		m_viewHeight{viewHeight}
	{ }

	void OrthographicCamera::updateProjectionMatrix()
	{
		float viewWidth = m_aspectRatio * m_viewHeight;
		m_projectionMatrix = glm::ortho(-viewWidth / 2, viewWidth / 2, -m_viewHeight / 2,
			m_viewHeight / 2, m_nearPlane, m_farPlane);
	}
}
