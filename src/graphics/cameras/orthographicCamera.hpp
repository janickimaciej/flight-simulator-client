#pragma once

#include "graphics/cameras/camera.hpp"

namespace Graphics
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float width, float nearPlane, float farPlane);
		virtual void updateProjectionMatrix() override;
		virtual ~OrthographicCamera() = default;

	private:
		float m_width{};
	};
}
