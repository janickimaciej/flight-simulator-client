#include "graphics/maps/islandMap.hpp"

#include "common/terrains/maps.hpp"

#include <glm/glm.hpp>

#include <algorithm>
#include <utility>

namespace Graphics
{
	static constexpr glm::vec3 moonLight{0.2, 0.2, 0.2};
	static constexpr glm::vec3 sunLight{1, 1, 1};

	IslandMap::IslandMap(WorldShading& worldShading) :
		m_moon{moonLight},
		m_sun{sunLight},
		m_dayNightCycle{m_moon, m_sun, worldShading}
	{
		setModels();
	}

	void IslandMap::update(const glm::vec3& cameraPos, int day, float timeOfDay)
	{
		m_sea.setPos({cameraPos.x, 0, cameraPos.z});
		m_dayNightCycle.setDay(day);
		m_dayNightCycle.setTimeOfDay(timeOfDay);
		m_dayNightCycle.updateWorldShading();
	}

	void IslandMap::updateShaders()
	{
		m_island.updateShaders();
		m_moon.updateShaders();
		m_sun.updateShaders();
	}

	void IslandMap::renderWater() const
	{
		m_sea.render();
	}

	void IslandMap::renderLand() const
	{
		m_island.render();
	}

	float IslandMap::getHeight(float x, float z) const
	{
		return std::max(m_seaTerrain->height(x, z), m_islandTerrain->height(x, z));
	}

	void IslandMap::setModels()
	{
		static constexpr float moonRotationPitchDeg = -15;
		static constexpr float moonRotationYawDeg = 75;
		m_moon.rotatePitch(glm::radians(moonRotationPitchDeg));
		m_moon.rotateYaw(glm::radians(moonRotationYawDeg));

		static constexpr float sunRotationPitchDeg = -15;
		static constexpr float sunRotationYawDeg = 75;
		m_sun.rotatePitch(glm::radians(sunRotationPitchDeg));
		m_sun.rotateYaw(glm::radians(sunRotationYawDeg));
	}
}
