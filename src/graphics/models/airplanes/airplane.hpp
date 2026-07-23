#pragma once

#include "common/airplaneCtrl.hpp"
#include "common/airplaneType.hpp"
#include "graphics/models/model.hpp"

#include <memory>

namespace Graphics
{
	class Airplane : public Model
	{
	public:
		virtual ~Airplane() = default;

		static std::unique_ptr<Airplane> createAirplane(Common::AirplaneType airplaneType);
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) = 0;
		virtual int getHP() const;
		virtual void setHP(int hp);

	protected:
		int m_hp{};
	};
}
