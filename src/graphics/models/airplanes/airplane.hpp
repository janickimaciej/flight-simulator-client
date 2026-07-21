#pragma once

#include "common/airplaneCtrl.hpp"
#include "common/airplaneType.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/texture.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class Airplane : public Model
	{
	public:
		static std::unique_ptr<Airplane> createAirplane(Common::AirplaneType airplaneType);
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) = 0;
		virtual int getHP() const;
		virtual void setHP(int hp);
		virtual ~Airplane() = default;

	protected:
		int m_hp{};
	};
}
