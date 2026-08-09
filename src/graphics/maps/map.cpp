#include "graphics/maps/map.hpp"

#include "graphics/maps/islandMap.hpp"

namespace Graphics
{
	std::unique_ptr<Map> Map::create(Common::MapName map, WorldShading& worldShading)
	{
		switch (map)
		{
			case Common::MapName::island:
				return std::make_unique<IslandMap>(worldShading);
		}
		return {};
	}
}
