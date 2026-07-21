#pragma once

#include "common/mapName.hpp"
#include "common/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/texture.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class Map
	{
	public:
		virtual void update(int day, float timeOfDay) = 0;
		virtual void updateShaders() = 0;
		virtual void render() const = 0;
		float getHeight(float x, float z) const;
		virtual ~Map() = default;

		static std::unique_ptr<Map> createMap(Common::MapName map, WorldShading& worldShading);

	protected:
		const std::unique_ptr<Common::Maps::Map> m_terrain{};

		Map(std::unique_ptr<Common::Maps::Map> terrain);
	};
}
