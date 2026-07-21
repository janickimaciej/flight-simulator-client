#include "graphics/models/airplanes/airplane.hpp"

#include "common/airplaneCtrl.hpp"
#include "common/airplaneType.hpp"
#include "graphics/lights/spotLight.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/models/airplanes/jw1.hpp"
#include "graphics/models/airplanes/mustang.hpp"
#include "graphics/path.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	std::unique_ptr<Airplane> Airplane::createAirplane(Common::AirplaneType airplaneType)
	{
		switch (airplaneType)
		{
			case Common::AirplaneType::mustang:
				return std::make_unique<Mustang>();

			case Common::AirplaneType::jw1:
				return std::make_unique<JW1>();
		}
		return nullptr;
	}

	int Airplane::getHP() const
	{
		return m_hp;
	}

	void Airplane::setHP(int hp)
	{
		m_hp = hp;
	}
}
