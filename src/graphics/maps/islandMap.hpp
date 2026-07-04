#pragma once

#include "common/maps/map.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/dayNightCycle.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/models/directionalLightModel.hpp"
#include "graphics/models/island.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class IslandMap : public Map
	{
	public:
		IslandMap(WorldShading& worldShading,
			AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
			AssetManager<std::string, const Texture>& textureManager,
			std::unique_ptr<Common::Maps::Map> terrain);
		virtual void update(int day, float timeOfDay) override;
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~IslandMap() = default;

	private:
		Island m_island;

		DirectionalLightModel m_moon;
		DirectionalLightModel m_sun;

		DayNightCycle m_dayNightCycle;

		void setModels();
	};
}
