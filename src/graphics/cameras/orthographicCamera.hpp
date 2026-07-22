#pragma once

#include "graphics/cameras/camera.hpp"

namespace Graphics
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float width, float nearPlane, float farPlane);
		virtual ~OrthographicCamera() = default;

		virtual void updateProjectionMatrix() override;

	private:
		float m_width{};
	};
}
