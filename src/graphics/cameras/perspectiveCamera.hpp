#pragma once

#include "graphics/cameras/camera.hpp"

namespace Graphics
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float nearPlane, float farPlane, float fovYRad);
		virtual ~PerspectiveCamera() = default;

	private:
		float m_fovYRad{};

		virtual void updateProjectionMatrix() override;
	};
}
