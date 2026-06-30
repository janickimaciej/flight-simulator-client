#pragma once

#include <glm/glm.hpp>

namespace Graphics
{
	class WorldShading
	{
	public:
		void updateShaders() const;

		void setBackgroundColor(const glm::vec3& backgroundColor);
		void setAmbient(float ambient);
		void setFogGradient(float fogGradient);
		void setFogDensity(float fogDensity);

	private:
		glm::vec3 m_backgroundColor{};
		float m_ambient{};
		float m_fogGradient{};
		float m_fogDensity{};
	};
}
