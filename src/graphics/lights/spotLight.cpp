#include "graphics/lights/spotLight.hpp"

#include "graphics/lights/light.hpp"
#include "graphics/shaderPrograms.hpp"

#include <glm/glm.hpp>

#include <array>
#include <cstddef>
#include <string>

namespace Graphics
{
	const std::string prefix = "spotLights";

	SpotLight::SpotLight(const glm::vec3& color, float attenuationQuadratic,
		float attenuationLinear, float attenuationConstant, float cutoffInnerRad,
		float cutoffOuterRad) :
		Light{getAvailableId(), prefix, color},
		m_attenuationQuadratic{attenuationQuadratic},
		m_attenuationLinear{attenuationLinear},
		m_attenuationConstant{attenuationConstant},
		m_cutoffInnerRad{cutoffInnerRad},
		m_cutoffOuterRad{cutoffOuterRad}
	{ }

	SpotLight::SpotLight(const SpotLight& spotLight) :
		Light{getAvailableId(), prefix, spotLight.m_color, spotLight.getState()},
		m_attenuationQuadratic{spotLight.m_attenuationQuadratic},
		m_attenuationLinear{spotLight.m_attenuationLinear},
		m_attenuationConstant{spotLight.m_attenuationConstant},
		m_cutoffInnerRad{spotLight.m_cutoffInnerRad},
		m_cutoffOuterRad{spotLight.m_cutoffOuterRad}
	{ }

	SpotLight::SpotLight(SpotLight&& spotLight) noexcept :
		Light{spotLight.m_id, prefix, spotLight.m_color,
			spotLight.getState()},
		m_attenuationQuadratic{spotLight.m_attenuationQuadratic},
		m_attenuationLinear{spotLight.m_attenuationLinear},
		m_attenuationConstant{spotLight.m_attenuationConstant},
		m_cutoffInnerRad{spotLight.m_cutoffInnerRad},
		m_cutoffOuterRad{spotLight.m_cutoffOuterRad}
	{
		++m_isActive[m_id];
	}

	void SpotLight::updateShaders(const glm::mat4& modelMatrix) const
	{
		ShaderPrograms::surface->use();
		ShaderPrograms::surface->setUniform(m_prefix + "position",
			getGlobalPosition(modelMatrix));
		ShaderPrograms::surface->setUniform(m_prefix + "direction",
			getGlobalDirection(modelMatrix));
		ShaderPrograms::surface->setUniform(m_prefix + "color", m_color);
		ShaderPrograms::surface->setUniform(m_prefix + "attenuationQuadratic",
			m_attenuationQuadratic);
		ShaderPrograms::surface->setUniform(m_prefix + "attenuationLinear", m_attenuationLinear);
		ShaderPrograms::surface->setUniform(m_prefix + "attenuationConstant",
			m_attenuationConstant);
		ShaderPrograms::surface->setUniform(m_prefix + "cutoffInnerRad", m_cutoffInnerRad);
		ShaderPrograms::surface->setUniform(m_prefix + "cutoffOuterRad", m_cutoffOuterRad);
	}

	SpotLight::~SpotLight()
	{
		--m_isActive[m_id];

		if (m_isActive[m_id] == 0)
		{
			ShaderPrograms::surface->use();
			ShaderPrograms::surface->setUniform(m_prefix + "isActive", false);
		}
	}

	std::array<int, SpotLight::maxSpotLightCount> SpotLight::m_isActive{};

	unsigned int SpotLight::getAvailableId()
	{
		unsigned int newId{};
		bool found = false;
		for (std::size_t i = 0; i < m_isActive.size(); ++i)
		{
			if (m_isActive.at(i) == 0)
			{
				++m_isActive.at(i);
				newId = static_cast<unsigned int>(i);
				found = true;
				break;
			}
		}
		assert(found);

		ShaderPrograms::surface->use();
		ShaderPrograms::surface->setUniform(prefix + "[" + std::to_string(newId) + "].isActive",
			true);

		return newId;
	}
}
