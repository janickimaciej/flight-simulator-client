#pragma once

#include "graphics/maps/map.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/models/model.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/textField.hpp"
#include "graphics/texture.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <vector>

namespace Graphics
{
	class HUD : public Model
	{
	public:
		HUD();

		virtual void updateShaders() override;
		virtual void render() const override;
		void update(const Airplane& ownAirplane, const Map& map, int playerCount);

	private:
		std::unique_ptr<TextField> m_fpsNumber{};
		std::unique_ptr<TextField> m_fpsUnit{};
		std::unique_ptr<TextField> m_playerCountNumber{};
		std::unique_ptr<TextField> m_playerCountUnit{};
		std::unique_ptr<TextField> m_airspeedText{};
		std::unique_ptr<TextField> m_airspeedNumber{};
		std::unique_ptr<TextField> m_airspeedUnit{};
		std::unique_ptr<TextField> m_verticalSpeedText{};
		std::unique_ptr<TextField> m_verticalSpeedNumber{};
		std::unique_ptr<TextField> m_verticalSpeedUnit{};
		std::unique_ptr<TextField> m_altitudeText{};
		std::unique_ptr<TextField> m_altitudeNumber{};
		std::unique_ptr<TextField> m_altitudeUnit{};
		std::unique_ptr<TextField> m_radarAltitudeText{};
		std::unique_ptr<TextField> m_radarAltitudeNumber{};
		std::unique_ptr<TextField> m_radarAltitudeUnit{};
		std::unique_ptr<TextField> m_hpNumber{};
		std::unique_ptr<TextField> m_hpUnit{};

		std::vector<std::shared_ptr<const Texture>> m_textureLocks{};

		float m_lastUpdateTime = 1;

		void renderHUD() const;
		void refresh(TextField& textField, int value, int numberOfDigits, bool isSigned);
	};
}
