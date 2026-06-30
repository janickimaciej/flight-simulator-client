#include "graphics/lights/directionalLight.hpp"

#include "graphics/lights/light.hpp"
#include "graphics/shaderPrograms.hpp"

#include <glm/glm.hpp>

#include <array>
#include <cstddef>
#include <string>

namespace Graphics
{
	const std::string prefix = "directionalLights";

	DirectionalLight::DirectionalLight(const glm::vec3& color) :
		Light{getAvailableId(), prefix, color}
	{ }

	DirectionalLight::DirectionalLight(const DirectionalLight& directionalLight) :
		Light{getAvailableId(), prefix, directionalLight.m_color, directionalLight.getState()}
	{ }

	DirectionalLight::DirectionalLight(DirectionalLight&& directionalLight) noexcept :
		Light{directionalLight.m_id, prefix, directionalLight.m_color, directionalLight.getState()}
	{
		++m_isActive[m_id];
	}

	void DirectionalLight::updateShaders(const glm::mat4& modelMatrix) const
	{
		ShaderPrograms::surface->use();
		ShaderPrograms::surface->setUniform(m_prefix + "direction",
			getGlobalDirection(modelMatrix));
		ShaderPrograms::surface->setUniform(m_prefix + "color", m_color);
	}

	DirectionalLight::~DirectionalLight()
	{
		--m_isActive[m_id];

		if (m_isActive[m_id] == 0)
		{
			ShaderPrograms::surface->use();
			ShaderPrograms::surface->setUniform(m_prefix + "isActive", false);
		}
	}

	std::array<int, DirectionalLight::maxDirectionalLightCount> DirectionalLight::m_isActive{};

	unsigned int DirectionalLight::getAvailableId()
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
