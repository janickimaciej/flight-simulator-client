#include "graphics/cameras/modelCamera.hpp"

#include "graphics/cameras/perspectiveCamera.hpp"
#include "graphics/models/model.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	ModelCamera::ModelCamera(const Model& model, float fovRad, float nearPlane, float farPlane) :
		PerspectiveCamera{fovRad, nearPlane, farPlane},
		m_model{model}
	{ }

	glm::mat4 ModelCamera::getCameraMatrix() const
	{
		return m_model.getModelMatrix() * getMatrix();
	}
}
