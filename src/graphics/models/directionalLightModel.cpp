#include "graphics/models/directionalLightModel.hpp"

namespace Graphics
{
	DirectionalLightModel::DirectionalLightModel(const glm::vec3& lightColor) :
		m_light{lightColor}
	{ }

	void DirectionalLightModel::setLightColor(const glm::vec3& color)
	{
		m_light.setColor(color);
	}

	void DirectionalLightModel::updateShaders()
	{
		m_light.updateShaders(getMatrix());
	}

	void DirectionalLightModel::render() const
	{ }
}
