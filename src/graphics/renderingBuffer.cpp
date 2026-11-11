#include "graphics/renderingBuffer.hpp"

namespace Graphics
{
	const Common::SceneInfo& RenderingBuffer::getLastUpdated()
	{
		{
			std::scoped_lock lock{m_mutex};
			m_locked = m_lastUpdated;
		}

		return m_buffer[m_locked];
	}

	void RenderingBuffer::update(const Common::SceneInfo& sceneInfo)
	{
		unsigned int index{};
		{
			std::scoped_lock lock{m_mutex};
			index = (m_lastUpdated + 1) % 3 == m_locked ?
				(m_locked + 1) % 3 : (m_lastUpdated + 1) % 3;
		}

		m_buffer[index] = sceneInfo;

		{
			std::scoped_lock lock{m_mutex};
			m_lastUpdated = index;
		}
	}
}
