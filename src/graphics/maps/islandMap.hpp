#pragma once

#include "common/terrains/maps.hpp"
#include "common/terrains/terrain.hpp"
#include "graphics/dayNightCycle.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/models/directionalLightModel.hpp"
#include "graphics/models/island.hpp"
#include "graphics/models/sea.hpp"
#include "graphics/worldShading.hpp"

#include <memory>

namespace Graphics
{
	class IslandMap : public Map
	{
	public:
		IslandMap(WorldShading& worldShading);
		virtual ~IslandMap() = default;

		virtual void update(const glm::vec3& cameraPos, int day, float timeOfDay) override;
		virtual void updateShaders() override;
		virtual void renderWater() const override;
		virtual void renderLand() const override;
		virtual float getHeight(float x, float z) const override;

	private:
		std::unique_ptr<Common::Terrains::Terrain> m_seaTerrain = Common::Terrains::Maps::sea();
		std::unique_ptr<Common::Terrains::Terrain> m_islandTerrain =
			Common::Terrains::Maps::island();

		Sea m_sea{};
		Island m_island{};

		DirectionalLightModel m_moon;
		DirectionalLightModel m_sun;

		DayNightCycle m_dayNightCycle;

		void setModels();
	};
}
