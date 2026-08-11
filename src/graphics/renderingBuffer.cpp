#include "graphics/renderingBuffer.hpp"

namespace Graphics
{
	RenderingBuffer::RenderingBuffer(int ownId) :
		m_ownId{ownId}
	{ }

	void RenderingBuffer::initialize(const glm::ivec2& viewportSize,
		Common::AirplaneType ownAirplaneType, Common::MapName map)
	{
		m_scene = std::make_unique<Scene>(viewportSize, m_ownId, ownAirplaneType, map);
	}

	void RenderingBuffer::updateBuffer(const Common::SceneInfo& sceneInfo)
	{
		unsigned int index{};
		{
			std::scoped_lock lock{m_mutex};

			index = (m_lastUpdated + 1) % 3 == m_beingRendered ?
				(m_beingRendered + 1) % 3 : (m_lastUpdated + 1) % 3;
		}

		m_buffer[index] = sceneInfo;

		{
			std::scoped_lock lock{m_mutex};

			m_lastUpdated = index;
		}
	}

	void RenderingBuffer::updateAndRenderScene(const glm::ivec2& viewportSize)
	{
		unsigned int index{};
		{
			std::scoped_lock lock{m_mutex};

			index = m_lastUpdated;
			m_beingRendered = index;
		}

		m_scene->update(m_buffer[index]);
		m_scene->updateShaders();
		m_scene->render(viewportSize);
	}
}
