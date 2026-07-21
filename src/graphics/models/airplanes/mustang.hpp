#pragma once

#include "common/airplaneCtrl.hpp"
#include "graphics/lights/spotLight.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/submodels/lightSubmodel.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class Mustang : public Airplane
	{
	public:
		Mustang();
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual void setCtrl(const Common::AirplaneCtrl& airplaneCtrl) override;
		virtual void setHP(int hp) override;

	private:
		std::unique_ptr<Submodel> m_cap{};
		std::unique_ptr<Submodel> m_propeller{};
		std::unique_ptr<Submodel> m_body{};
		std::unique_ptr<Submodel> m_joins{};
		std::unique_ptr<Submodel> m_tires{};
		std::unique_ptr<SpotLight> m_leftLight{};
		std::unique_ptr<LightSubmodel> m_leftLightSubmodel{};
		std::unique_ptr<SpotLight> m_rightLight{};
		std::unique_ptr<LightSubmodel> m_rightLightSubmodel{};

		bool m_isDestroyed = false;
		float m_propellerAngVelocityDeg{};

		void renderSurfaces() const;
		void renderLights() const;
	};
}
