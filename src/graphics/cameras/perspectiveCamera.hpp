#pragma once

#include "graphics/cameras/camera.hpp"

namespace Graphics
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fovRad, float nearPlane, float farPlane);
		virtual ~PerspectiveCamera() = default;

		virtual void updateProjectionMatrix() override;

	private:
		float m_fovRad{};
	};
}
