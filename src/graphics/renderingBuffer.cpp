#include "graphics/renderingBuffer.hpp"

namespace Graphics
{
	RenderingBuffer::RenderingBuffer(int ownId) :
		m_ownId{ownId}
	{ }

	void RenderingBuffer::initialize(Common::AirplaneType ownAirplaneType, Common::MapName map)
	{
		m_scene = std::make_unique<Scene>(m_ownId, ownAirplaneType, map);
	}

	void RenderingBuffer::updateBuffer(const Common::SceneInfo& sceneInfo)
	{
		m_mutex.lock();

		unsigned int index = (m_lastUpdated + 1) % 3 == m_beingRendered ?
			(m_beingRendered + 1) % 3 : (m_lastUpdated + 1) % 3;

		m_mutex.unlock();

		m_buffer[index] = sceneInfo;

		m_mutex.lock();

		m_lastUpdated = index;

		m_mutex.unlock();
	}

	void RenderingBuffer::updateAndRenderScene(float aspectRatio)
	{
		m_mutex.lock();

		unsigned int index = m_lastUpdated;
		m_beingRendered = index;

		m_mutex.unlock();

		m_scene->update(m_buffer[index]);
		m_scene->updateShaders();
		m_scene->render(aspectRatio);
	}
}
