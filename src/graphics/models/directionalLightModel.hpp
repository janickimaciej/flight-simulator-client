#pragma once

#include "graphics/lights/directionalLight.hpp"
#include "graphics/models/model.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class DirectionalLightModel : public Model
	{
	public:
		DirectionalLightModel(const glm::vec3& lightColor);
		virtual ~DirectionalLightModel() = default;

		void setLightColor(const glm::vec3& color);
		virtual void updateShaders() override;
		virtual void render() const override;

	private:
		DirectionalLight m_light;
	};
}
