#pragma once

#include "graphics/cameras/camera.hpp"

namespace Graphics
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fovRad, float nearPlane, float farPlane);
		virtual void updateProjectionMatrix() override;
		virtual ~PerspectiveCamera() = default;

	private:
		float m_fovRad{};
	};
}
