#include "graphics/cameras/modelCamera.hpp"

namespace Graphics
{
	ModelCamera::ModelCamera(float nearPlane, float farPlane, float fovYRad, const Model& model) :
		PerspectiveCamera{nearPlane, farPlane, fovYRad},
		m_model{model}
	{ }

	glm::mat4 ModelCamera::getViewMatrixInverse() const
	{
		return m_model.getModelMatrix() * getMatrix();
	}
}
