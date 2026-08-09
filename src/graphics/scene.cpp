#include "graphics/scene.hpp"

#include "graphics/airplaneCameraPoss.hpp"
#include "graphics/cameras/modelCamera.hpp"
#include "graphics/cameras/orthographicCamera.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <cstddef>
#include <utility>

namespace Graphics
{
	Scene::Scene(int ownId, Common::AirplaneType ownAirplaneType, Common::MapName map) :
		m_ownId{ownId},
		m_ownAirplaneType{ownAirplaneType},
		m_hud{}
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_airplanes.insert({ownId, Airplane::createAirplane(ownAirplaneType)});

		static constexpr float worldCameraNearPlane = 4;
		static constexpr float worldCameraFarPlane = 20000;
		static constexpr float worldCameraFOVYDeg = 60;
		m_worldCamera = std::make_unique<ModelCamera>(worldCameraNearPlane, worldCameraFarPlane,
			glm::radians(worldCameraFOVYDeg), *m_airplanes.at(ownId));
		static constexpr float cameraPitchDeg = -10;
		m_worldCamera->rotatePitch(glm::radians(cameraPitchDeg));
		m_worldCamera->setPos(airplaneCameraPoss[Common::toSizeT(ownAirplaneType)]);

		static constexpr float hudCameraNearPlane = 0;
		static constexpr float hudCameraFarPlane = 1;
		static constexpr float hudCameraViewHeight = 2;
		m_hudCamera = std::make_unique<OrthographicCamera>(hudCameraNearPlane, hudCameraFarPlane,
			hudCameraViewHeight);

		m_map = Map::create(map, m_worldShading);
	}

	void Scene::update(const Common::SceneInfo& sceneInfo)
	{
		m_map->update(sceneInfo.day, sceneInfo.timeOfDay);
		addAndUpdateAirplanes(sceneInfo.airplaneInfos);
		removeAirplanes(sceneInfo.airplaneInfos);
		updateBullets(sceneInfo.bulletInfos);
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

	void Scene::render(float aspectRatio)
	{
		m_worldCamera->use(aspectRatio);
		m_map->render();
		for (const std::pair<const int, std::unique_ptr<Airplane>>& airplane : m_airplanes)
		{
			airplane.second->render();
		}
		for (const std::unique_ptr<Bullet>& bullet : m_bullets)
		{
			bullet->render();
		}

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
