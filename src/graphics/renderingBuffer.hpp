#pragma once

#include "common/airplaneType.hpp"
#include "common/mapName.hpp"
#include "common/sceneInfo.hpp"

#include <array>
#include <mutex>

namespace Graphics
{
	class RenderingBuffer
	{
	public:
		const Common::SceneInfo& getLastUpdated();
		void update(const Common::SceneInfo& sceneInfo);

	private:
		static const int m_bufferSize = 3;
		std::array<Common::SceneInfo, m_bufferSize> m_buffer{};

		unsigned int m_lastUpdated{};
		unsigned int m_locked{};
		std::mutex m_mutex{};
	};
}
