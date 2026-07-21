#include "graphics/models/airplanes/mustang.hpp"

#include "common/airplaneCentersOfMass.hpp"
#include "common/airplaneCtrl.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderPrograms.hpp"
#include "graphics/texture.hpp"
#include "graphics/time.hpp"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
	static const std::string modelName = "mustang";

	static const std::string capPath = meshPath(modelName, "cap");
	static const std::string propellerPath = meshPath(modelName, "propeller");
	static const std::string fuselagePath = meshPath(modelName, "body");
	static const std::string joinsPath = meshPath(modelName, "joins");
	static const std::string tiresPath = meshPath(modelName, "tires");
	static const std::string lightPath = meshPath(modelName, "light");

	static const std::string camoPath = texturePath(modelName, "camo");

	static constexpr float lightsAttenuationQuadratic = 0.0001f;
	static constexpr float lightsAttenuationLinear = 0.0005f;
	static constexpr float lightsAttenuationConstant = 1;
	static constexpr glm::vec3 lightsColor{1, 1, 1};
	static constexpr float lightsCutoffInnerDeg = 8;
	static constexpr float lightsCutoffOuterDeg = 10;

	static const Material texturedMetal{glm::vec3{1, 1, 1}, 0.75f, 0.5f, 30, true};
	static const Material metal{glm::vec3{0.25f, 0.25f, 0.25f}, 0.75f, 0.5f, 30, true};
	static const Material rubber{glm::vec3{0.1f, 0.1f, 0.1f}, 0.75f, 0, 1, false};
	static const Material whiteLightGlass{glm::vec3{1, 1, 1}, 1, 1, 1, false};

	Mustang::Mustang()
	{
		auto& fileMeshManager = AssetManager<std::string, const Mesh>::instance();
		auto& textureManager = AssetManager<std::string, const Texture>::instance();

		m_cap = std::make_unique<Submodel>(*ShaderPrograms::surface, fileMeshManager.get(capPath),
			metal);
		m_propeller = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(propellerPath), metal);
		m_body = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(fuselagePath), texturedMetal, textureManager.get(camoPath));
		m_joins = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(joinsPath), metal);
		m_tires = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(tiresPath), rubber);
		m_leftLight = std::make_unique<SpotLight>(lightsColor, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, glm::radians(lightsCutoffInnerDeg),
			glm::radians(lightsCutoffOuterDeg));
		m_leftLightSubmodel = std::make_unique<LightSubmodel>(*m_leftLight,
			fileMeshManager.get(lightPath), whiteLightGlass);
		m_rightLight = std::make_unique<SpotLight>(lightsColor, lightsAttenuationQuadratic,
			lightsAttenuationLinear, lightsAttenuationConstant, glm::radians(lightsCutoffInnerDeg),
			glm::radians(lightsCutoffOuterDeg));
		m_rightLightSubmodel = std::make_unique<LightSubmodel>(*m_rightLight,
			fileMeshManager.get(lightPath), whiteLightGlass);

		static constexpr float lightsPosXAbs = 2.14f;
		static constexpr float lightsPosY = -0.474f;
		static constexpr float lightsPosZ = 2.938f;
		m_leftLight->translate(glm::vec3{lightsPosXAbs, lightsPosY, lightsPosZ});
		m_rightLight->translate(glm::vec3{-lightsPosXAbs, lightsPosY, lightsPosZ});

		static constexpr glm::vec3 nosePos = -Common::airplaneCentersOfMass[
			toSizeT(Common::AirplaneType::mustang)];
		m_cap->translate(nosePos);
		m_propeller->translate(nosePos);
		m_body->translate(nosePos);
		m_joins->translate(nosePos);
		m_tires->translate(nosePos);
		m_leftLight->translate(nosePos);
		m_rightLight->translate(nosePos);
	}

	void Mustang::updateShaders()
	{
		m_leftLight->updateShaders(getMatrix());
		m_rightLight->updateShaders(getMatrix());
	}

	void Mustang::render() const
	{
		ShaderPrograms::surface->use();
		renderSurfaces();

		ShaderPrograms::light->use();
		renderLights();
	}

	void Mustang::setCtrl(const Common::AirplaneCtrl& airplaneCtrl)
	{
		static constexpr float maxPropellerAngVelocityDeg = 2 * 360;
		m_propellerAngVelocityDeg = airplaneCtrl.thrustRelative * maxPropellerAngVelocityDeg;
		m_propeller->rotateRoll(glm::radians(m_propellerAngVelocityDeg) * Time::getDeltaTime());
	}

	void Mustang::setHP(int hp)
	{
		static const Material red{glm::vec3{1, 0, 0}, 1, 0, 1, false};
		if (!m_isDestroyed && hp == 0)
		{
			m_cap->setMaterial(red);
			m_propeller->setMaterial(red);
			m_body->setMaterial(red);
			m_joins->setMaterial(red);
			m_tires->setMaterial(red);
			m_leftLightSubmodel->setMaterial(red);
			m_rightLightSubmodel->setMaterial(red);
			m_isDestroyed = true;
		}
		else if (m_isDestroyed && hp > 0)
		{
			m_cap->setMaterial(metal);
			m_propeller->setMaterial(metal);
			m_body->setMaterial(texturedMetal);
			m_joins->setMaterial(metal);
			m_tires->setMaterial(rubber);
			m_leftLightSubmodel->setMaterial(whiteLightGlass);
			m_rightLightSubmodel->setMaterial(whiteLightGlass);
			m_isDestroyed = false;
		}
		Airplane::setHP(hp);
	}

	void Mustang::renderSurfaces() const
	{
		m_cap->render(getMatrix());
		m_propeller->render(getMatrix());
		m_body->render(getMatrix());
		m_joins->render(getMatrix());
		m_tires->render(getMatrix());
	}

	void Mustang::renderLights() const
	{
		m_leftLightSubmodel->render(getMatrix());
		m_rightLightSubmodel->render(getMatrix());
	}
}
