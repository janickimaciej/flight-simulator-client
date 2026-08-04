#pragma once

#include "common/transformable.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class Camera : public Common::Transformable
	{
	public:
		virtual ~Camera() = default;

		virtual void use(float aspectRatio);

	protected:
		const float m_nearPlane{};
		const float m_farPlane{};
		float m_aspectRatio{};
		glm::mat4 m_projectionMatrix{};

		Camera(float nearPlane, float farPlane);

	private:
		virtual glm::mat4 getViewMatrixInverse() const;
		virtual void updateProjectionMatrix() = 0;
		glm::vec3 getWorldPos() const;
		void updateShaders() const;
	};
}
