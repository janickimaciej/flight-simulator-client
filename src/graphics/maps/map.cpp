#include "graphics/maps/map.hpp"

#include "common/maps/islandMap.hpp"
#include "graphics/maps/islandMap.hpp"

#include <utility>

namespace Graphics
{
	std::unique_ptr<Map> Map::createMap(Common::MapName map, WorldShading& worldShading)
	{
		switch (map)
		{
			case Common::MapName::island:
				return std::make_unique<IslandMap>(worldShading,
					std::make_unique<Common::Maps::IslandMap>());
		}
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
