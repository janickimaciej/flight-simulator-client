#include "graphics/maps/map.hpp"

#include "common/mapName.hpp"
#include "common/maps/airportMap.hpp"
#include "common/maps/islandMap.hpp"
#include "common/maps/map.hpp"
#include "graphics/maps/airportMap.hpp"
#include "graphics/maps/islandMap.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	std::unique_ptr<Map> Map::createMap(Common::MapName map, WorldShading& worldShading,
		AssetManager<std::string, const Mesh>& fileMeshManager,
		AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
		AssetManager<std::string, const Texture>& textureManager)
	{
		switch (map)
		{
			case Common::MapName::airport:
				return std::make_unique<AirportMap>(worldShading, fileMeshManager, textureManager,
					std::make_unique<Common::Maps::AirportMap>());

			case Common::MapName::island:
				return std::make_unique<IslandMap>(worldShading, proceduralMeshManager,
					textureManager, std::make_unique<Common::Maps::IslandMap>());
		}
		assert(false);
		return nullptr;
	}

	float Map::getHeight(float x, float z) const
	{
		return m_terrain->terrain().height(x, z);
	}

	Map::Map(std::unique_ptr<Common::Maps::Map> terrain) :
		m_terrain{std::move(terrain)}
	{ }
}
