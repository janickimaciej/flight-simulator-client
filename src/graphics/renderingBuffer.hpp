#pragma once

#include "common/airplaneType.hpp"
#include "common/mapName.hpp"
#include "common/sceneInfo.hpp"
#include "graphics/scene.hpp"

#include <array>
#include <memory>
#include <mutex>

namespace Graphics
{
	class RenderingBuffer
	{
	public:
		RenderingBuffer(int ownId);

		void initialize(const glm::ivec2& viewportSize, Common::AirplaneType ownAirplaneType,
			Common::MapName map);
		void updateBuffer(const Common::SceneInfo& sceneInfo);
		void updateAndRenderScene(const glm::ivec2& viewportSize);

	private:
		static const int m_bufferSize = 3;
		std::array<Common::SceneInfo, m_bufferSize> m_buffer{};
		int m_ownId{};
		std::unique_ptr<Scene> m_scene{};

		unsigned int m_lastUpdated{};
		unsigned int m_beingRendered{};
		std::mutex m_mutex{};
	};
}
