#pragma once

#include "common/mapName.hpp"
#include "graphics/worldShading.hpp"

#include <memory>

namespace Graphics
{
	class Map
	{
	public:
		virtual ~Map() = default;

		virtual void update(int day, float timeOfDay) = 0;
		virtual void updateShaders() = 0;
		virtual void renderSea() const = 0;
		virtual void renderLand() const = 0;
		virtual float getHeight(float x, float z) const = 0;

		static std::unique_ptr<Map> create(Common::MapName map, WorldShading& worldShading);
	};
}
