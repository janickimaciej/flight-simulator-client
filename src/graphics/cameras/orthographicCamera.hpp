#pragma once

#include "graphics/cameras/camera.hpp"

namespace Graphics
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float nearPlane, float farPlane, float viewHeight);
		virtual ~OrthographicCamera() = default;

	private:
		float m_viewHeight{};

		virtual void updateProjectionMatrix() override;
	};
}
