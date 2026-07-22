#pragma once

#include "common/transformable.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class Camera : public Common::Transformable
	{
	public:
		virtual ~Camera() = default;

		virtual void updateProjectionMatrix() = 0;
		virtual void use(float aspectRatio);

	protected:
		glm::mat4 m_projectionMatrix{};
		float m_aspectRatio{};
		const float m_nearPlane{};
		const float m_farPlane{};

		Camera(float nearPlane, float farPlane);
		virtual glm::mat4 getCameraMatrix() const;
		glm::vec3 getCameraPos() const;
		glm::mat4 getViewMatrix() const;
	};
}
