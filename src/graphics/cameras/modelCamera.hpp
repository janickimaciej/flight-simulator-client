#pragma once

#include "graphics/cameras/perspectiveCamera.hpp"
#include "graphics/models/model.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class ModelCamera : public PerspectiveCamera
	{
	public:
		ModelCamera(float nearPlane, float farPlane, float fovYRad, const Model& model);
		virtual ~ModelCamera() = default;

	private:
		const Model& m_model;

		virtual glm::mat4 getViewMatrixInverse() const override;
	};
}
