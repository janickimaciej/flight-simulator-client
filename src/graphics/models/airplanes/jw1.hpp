#pragma once

#include "common/airplaneCtrl.hpp"
#include "graphics/lights/pointLight.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class JW1 : public Airplane
	{
	public:
		JW1();

		virtual void updateShaders() override;
		virtual void render() const override;
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) override;
		virtual void setHP(int hp) override;

	private:
		std::unique_ptr<Submodel> m_cone{};
		std::unique_ptr<Submodel> m_gun{};
		std::unique_ptr<Submodel> m_cockpit{};
		std::unique_ptr<Submodel> m_fuselage{};
		std::unique_ptr<Submodel> m_leftEngine{};
		std::unique_ptr<Submodel> m_rightEngine{};
		std::unique_ptr<Submodel> m_leftNozzle{};
		std::unique_ptr<Submodel> m_rightNozzle{};
		std::unique_ptr<Submodel> m_leftNozzleGlass{};
		std::unique_ptr<Submodel> m_rightNozzleGlass{};
		std::unique_ptr<Submodel> m_leftWing{};
		std::unique_ptr<Submodel> m_rightWing{};
		std::unique_ptr<Submodel> m_leftVStab{};
		std::unique_ptr<Submodel> m_rightVStab{};
		std::unique_ptr<Submodel> m_leftElevator{};
		std::unique_ptr<Submodel> m_rightElevator{};
		std::unique_ptr<Submodel> m_leftRudder{};
		std::unique_ptr<Submodel> m_rightRudder{};
		std::unique_ptr<Submodel> m_leftAileron{};
		std::unique_ptr<Submodel> m_rightAileron{};

		bool m_isDestroyed = false;

		void renderSurfaces() const;
		void renderLights() const;
	};
}
