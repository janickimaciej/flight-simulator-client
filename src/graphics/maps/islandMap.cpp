#include "graphics/maps/islandMap.hpp"

#include "common/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	static constexpr glm::vec3 moonLight{0.2, 0.2, 0.2};
	static constexpr glm::vec3 sunLight{1, 1, 1};

	IslandMap::IslandMap(WorldShading& worldShading,
		std::unique_ptr<Common::Maps::Map> terrain) :
		Map{std::move(terrain)},
		m_island{},
		m_moon{moonLight},
		m_sun{sunLight},
		m_dayNightCycle{m_moon, m_sun, worldShading}
	{
		setModels();
	}

	void IslandMap::update(int day, float timeOfDay)
	{
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

	void IslandMap::render() const
	{
		m_island.render();
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
