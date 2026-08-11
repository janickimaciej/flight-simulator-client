#pragma once

#include "common/mapName.hpp"
#include "graphics/worldShading.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace Graphics
{
	class Map
	{
	public:
		virtual ~Map() = default;

		virtual void update(const glm::vec3& cameraPos, int day, float timeOfDay) = 0;
		virtual void updateShaders() = 0;
		virtual void renderWater() const = 0;
		virtual void renderLand() const = 0;
		virtual float getHeight(float x, float z) const = 0;

		static std::unique_ptr<Map> create(Common::MapName map, WorldShading& worldShading);
	};
}
