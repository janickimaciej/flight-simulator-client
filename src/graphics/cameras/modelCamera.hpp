#pragma once

#include "graphics/cameras/perspectiveCamera.hpp"
#include "graphics/models/model.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class ModelCamera : public PerspectiveCamera
	{
	public:
		ModelCamera(const Model& model, float fovRad, float nearPlane, float farPlane);
		virtual ~ModelCamera() = default;

	protected:
		const Model& m_model;

		virtual glm::mat4 getCameraMatrix() const override;
	};
}
