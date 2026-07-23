#include "graphics/models/airplanes/airplane.hpp"

#include "graphics/models/airplanes/jw1.hpp"
#include "graphics/models/airplanes/mustang.hpp"

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
