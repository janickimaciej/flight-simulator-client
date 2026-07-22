#pragma once

#include "graphics/cameras/perspectiveCamera.hpp"
#include "graphics/models/model.hpp"

namespace Graphics
{
	class TrackingCamera : public PerspectiveCamera
	{
	public:
		TrackingCamera(float fovRad, float nearPlane, float farPlane, const Model& model);
		virtual ~TrackingCamera() = default;

		virtual void use(float aspectRatio) override;

	protected:
		const Model& m_model;

		void aimAtModel();
	};
}
