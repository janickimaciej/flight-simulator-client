#pragma once

#include "common/maps/map.hpp"
#include "graphics/dayNightCycle.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airport.hpp"
#include "graphics/models/directionalLightModel.hpp"
#include "graphics/models/zeppelin.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class AirportMap : public Map
	{
	public:
		AirportMap(WorldShading& worldShading,
			std::unique_ptr<Common::Maps::Map> terrain);
		virtual ~AirportMap() = default;

		virtual void update(int day, float timeOfDay) override;
		virtual void updateShaders() override;
		virtual void render() const override;

	private:
		Airport m_airport;
		Zeppelin m_zeppelin;

		DirectionalLightModel m_moon;
		DirectionalLightModel m_sun;

		DayNightCycle m_dayNightCycle;

		void setModels();
	};
}
