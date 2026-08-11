#pragma once

#include "common/airplaneInfo.hpp"
#include "common/airplaneType.hpp"
#include "common/bulletInfo.hpp"
#include "common/mapName.hpp"
#include "common/sceneInfo.hpp"
#include "graphics/cameras/camera.hpp"
#include "graphics/framebuffer.hpp"
#include "graphics/hud.hpp"
#include "graphics/maps/map.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/models/bullet.hpp"
#include "graphics/screenQuad.hpp"
#include "graphics/worldShading.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace Graphics
{
	class Scene
	{
	public:
		Scene(const glm::ivec2& viewportSize, int ownId, Common::AirplaneType ownAirplaneType,
			Common::MapName map);

		void update(const Common::SceneInfo& sceneInfo);
		void updateShaders();
		void render(const glm::ivec2& viewportSize);

	private:
		int m_ownId{};
		Common::AirplaneType m_ownAirplaneType{};

		std::unique_ptr<Map> m_map{};
		std::unordered_map<int, std::unique_ptr<Airplane>> m_airplanes{};
		std::vector<std::unique_ptr<Bullet>> m_bullets{};
		HUD m_hud;

		Framebuffer m_framebuffer;
		ScreenQuad m_screenQuad{};
		std::unique_ptr<Camera> m_worldCamera{};
		std::unique_ptr<Camera> m_hudCamera{};

		WorldShading m_worldShading{};

		void clearFramebuffer() const;
		void addAndUpdateAirplanes(
			const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos);
		void removeAirplanes(const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos);
		void updateBullets(const std::vector<Common::BulletInfo>& bulletInfos);
	};
}
