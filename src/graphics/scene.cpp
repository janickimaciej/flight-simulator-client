#include "graphics/scene.hpp"

#include "graphics/cameras/modelCamera.hpp"
#include "graphics/cameras/orthographicCamera.hpp"
#include "graphics/config.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <cstddef>
#include <utility>

namespace Graphics
{
	Scene::Scene(const glm::ivec2& viewportSize, int ownId, Common::AirplaneType ownAirplaneType,
		Common::MapName map) :
		m_ownId{ownId},
		m_ownAirplaneType{ownAirplaneType},
		m_hud{},
		m_defaultFramebuffer{viewportSize},
		m_waterFramebuffer{viewportSize}
	{
		m_waterFramebuffer.colorTexture().depthTexture();

		glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_airplanes.insert({ownId, Airplane::createAirplane(ownAirplaneType)});

		m_worldCamera = std::make_unique<ModelCamera>(worldCameraNearPlane, worldCameraFarPlane,
			glm::radians(worldCameraFOVYDeg), *m_airplanes.at(ownId));
		static constexpr float cameraPitchDeg = -10;
		m_worldCamera->rotatePitch(glm::radians(cameraPitchDeg));
		m_worldCamera->setPos({0, 10, 25});

		static constexpr float hudCameraNearPlane = 0;
		static constexpr float hudCameraFarPlane = 1;
		static constexpr float hudCameraViewHeight = 2;
		m_hudCamera = std::make_unique<OrthographicCamera>(hudCameraNearPlane, hudCameraFarPlane,
			hudCameraViewHeight);

		m_map = Map::create(map, m_worldShading);
	}

	void Scene::update(const Common::SceneInfo& sceneInfo)
	{
		addAndUpdateAirplanes(sceneInfo.airplaneInfos);
		removeAirplanes(sceneInfo.airplaneInfos);
		updateBullets(sceneInfo.bulletInfos);
		m_map->update(m_airplanes[m_ownId]->getPos(), sceneInfo.day, sceneInfo.timeOfDay);
		m_hud.update(*m_airplanes[m_ownId], *m_map, static_cast<int>(m_airplanes.size()));
	}

	void Scene::updateShaders()
	{
		m_map->updateShaders();
		for (std::pair<const int, std::unique_ptr<Airplane>>& airplane : m_airplanes)
		{
			airplane.second->updateShaders();
		}
		m_worldShading.updateShaders();
	}

	void Scene::render(const glm::ivec2& viewportSize)
	{
		m_defaultFramebuffer.setSize(viewportSize);
		m_waterFramebuffer.setSize(viewportSize);
		float aspectRatio = static_cast<float>(viewportSize.x) / viewportSize.y;
		m_worldCamera->use(aspectRatio);

		m_defaultFramebuffer.bind();
		m_defaultFramebuffer.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
			m_worldShading.getBackgroundColor());
		glDisable(GL_DEPTH_TEST);
		m_map->renderWater();
		Framebuffer::blit(GL_COLOR_BUFFER_BIT, m_defaultFramebuffer, m_waterFramebuffer);

		m_defaultFramebuffer.bind();
		glEnable(GL_DEPTH_TEST);
		m_map->renderLand();
		Framebuffer::blit(GL_DEPTH_BUFFER_BIT, m_defaultFramebuffer, m_waterFramebuffer);

		m_defaultFramebuffer.bind();
		m_waterFramebuffer.bindColorTexture(0);
		m_waterFramebuffer.bindDepthTexture(1);
		m_map->blendWater(viewportSize);
		for (const std::pair<const int, std::unique_ptr<Airplane>>& airplane : m_airplanes)
		{
			airplane.second->render();
		}
		for (const std::unique_ptr<Bullet>& bullet : m_bullets)
		{
			bullet->render();
		}

		glDisable(GL_DEPTH_TEST);
		m_hudCamera->use(aspectRatio);
		m_hud.updateLayout(aspectRatio);
		m_hud.render();
	}

	void Scene::addAndUpdateAirplanes(
		const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos)
	{
		for (const std::pair<const int, Common::AirplaneInfo>& airplaneInfo : airplaneInfos)
		{
			if (!m_airplanes.contains(airplaneInfo.first))
			{
				m_airplanes.insert({airplaneInfo.first,
					Airplane::createAirplane(airplaneInfo.second.airplaneType)});
			}
			m_airplanes.at(airplaneInfo.first)->setState(airplaneInfo.second.state);
			m_airplanes.at(airplaneInfo.first)->setCtrl(airplaneInfo.second.airplaneCtrl);
			m_airplanes.at(airplaneInfo.first)->setHP(airplaneInfo.second.hp);
		}
	}

	void Scene::removeAirplanes(const std::unordered_map<int, Common::AirplaneInfo>& airplaneInfos)
	{
		std::vector<int> keysToBeDeleted;
		for (const std::pair<const int, std::unique_ptr<Airplane>>& airplane : m_airplanes)
		{
			if (!airplaneInfos.contains(airplane.first))
			{
				keysToBeDeleted.push_back(airplane.first);
			}
		}
		for (int key : keysToBeDeleted)
		{
			m_airplanes.erase(key);
		}
	}

	void Scene::updateBullets(const std::vector<Common::BulletInfo>& bulletInfos)
	{
		int sizeDiff = static_cast<int>(m_bullets.size()) - static_cast<int>(bulletInfos.size());
		if (m_bullets.size() > bulletInfos.size())
		{
			m_bullets.erase(m_bullets.end() - sizeDiff, m_bullets.end());
		}

		for (std::size_t i = m_bullets.size(); i < bulletInfos.size(); ++i)
		{
			m_bullets.push_back(std::make_unique<Bullet>());
		}

		for (std::size_t i = 0; i < bulletInfos.size(); ++i)
		{
			m_bullets.at(i)->setState(bulletInfos.at(i).state);
		}
	}
}
