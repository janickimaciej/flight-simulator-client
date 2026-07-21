#include "graphics/models/airplanes/jw1.hpp"

#include "common/airplaneCentersOfMass.hpp"
#include "common/airplaneCtrl.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/airplanes/airplane.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderPrograms.hpp"
#include "graphics/texture.hpp"

#include <string>

namespace Graphics
{
	static const std::string modelName = "jw1";

	static const std::string conePath = meshPath(modelName, "cone");
	static const std::string gunPath = meshPath(modelName, "gun");
	static const std::string cockpitPath = meshPath(modelName, "cockpit");
	static const std::string fuselagePath = meshPath(modelName, "fuselage");
	static const std::string rightEnginePath = meshPath(modelName, "rightEngine");
	static const std::string rightNozzlePath = meshPath(modelName, "rightNozzle");
	static const std::string rightNozzleGlassPath = meshPath(modelName, "rightNozzleGlass");
	static const std::string rightWingPath = meshPath(modelName, "rightWing");
	static const std::string rightVStabPath = meshPath(modelName, "rightVStab");
	static const std::string rightElevatorPath = meshPath(modelName, "rightElevator");
	static const std::string rightRudderPath = meshPath(modelName, "rightRudder");
	static const std::string rightAileronPath = meshPath(modelName, "rightAileron");

	static const std::string camoPath = texturePath(modelName, "camo");
	static const std::string nozzleGlassPath = texturePath(modelName, "nozzleGlass");

	static constexpr float lightsAttenuationQuadratic = 0.0001f;
	static constexpr float lightsAttenuationLinear = 0.0005f;
	static constexpr float lightsAttenuationConstant = 1;
	static constexpr glm::vec3 lightsColor{1, 1, 1};

	static const Material texturedMetal{glm::vec3{1, 1, 1}, 0.2f, 0.2f, 30, true};
	static const Material darkMetal{glm::vec3{0.4f, 0.4f, 0.4f}, 0.2f, 0.2f, 30, true};
	static const Material defaultNozzleGlass{glm::vec3{0, 0, 0}, 1, 1, 1, false};
	static const Material blackGlass{glm::vec3{0, 0, 0}, 0.75f, 1, 50, false};

	JW1::JW1()
	{
		auto& fileMeshManager = AssetManager<std::string, const Mesh>::instance();
		auto& textureManager = AssetManager<std::string, const Texture>::instance();

		m_cone = std::make_unique<Submodel>(*ShaderPrograms::surface, fileMeshManager.get(conePath),
			texturedMetal, textureManager.get(Texture::getId(camoPath)));
		m_gun = std::make_unique<Submodel>(*ShaderPrograms::surface, fileMeshManager.get(gunPath),
			texturedMetal, textureManager.get(Texture::getId(camoPath)));
		m_cockpit = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(cockpitPath), blackGlass);
		m_fuselage = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(fuselagePath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_leftEngine = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightEnginePath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_rightEngine = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightEnginePath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_leftNozzle = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightNozzlePath), darkMetal);
		m_rightNozzle = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightNozzlePath), darkMetal);
		m_leftNozzleGlass = std::make_unique<Submodel>(*ShaderPrograms::light,
			fileMeshManager.get(rightNozzleGlassPath), defaultNozzleGlass,
			textureManager.get(Texture::getId(nozzleGlassPath)));
		m_rightNozzleGlass = std::make_unique<Submodel>(*ShaderPrograms::light,
			fileMeshManager.get(rightNozzleGlassPath), defaultNozzleGlass,
			textureManager.get(Texture::getId(nozzleGlassPath)));
		m_leftWing = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightWingPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_rightWing = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightWingPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_leftVStab = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightVStabPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_rightVStab = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightVStabPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_leftElevator = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightElevatorPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_rightElevator = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightElevatorPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_leftRudder = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightRudderPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_rightRudder = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightRudderPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_leftAileron = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightAileronPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));
		m_rightAileron = std::make_unique<Submodel>(*ShaderPrograms::surface,
			fileMeshManager.get(rightAileronPath), texturedMetal,
			textureManager.get(Texture::getId(camoPath)));

		m_leftEngine->mirrorX();
		m_leftNozzle->mirrorX();
		m_leftNozzleGlass->mirrorX();
		m_leftWing->mirrorX();
		m_leftVStab->mirrorX();
		m_leftElevator->mirrorX();
		m_leftRudder->mirrorX();
		m_leftAileron->mirrorX();

		m_leftElevator->translate(glm::vec3{0, 0, 16.6f});
		m_rightElevator->translate(glm::vec3{0, 0, 16.6f});
		m_leftRudder->translate(glm::vec3{-1.375f, 0.533f, 18.92f});
		m_rightRudder->translate(glm::vec3{1.375f, 0.533f, 18.92f});
		m_leftAileron->translate(glm::vec3{-4.107f, 0.535f, 14.57f});
		m_rightAileron->translate(glm::vec3{4.107f, 0.535f, 14.57f});

		static constexpr glm::vec3 nosePos = -Common::airplaneCentersOfMass[
			toSizeT(Common::AirplaneType::jw1)];
		m_cone->translate(nosePos);
		m_gun->translate(nosePos);
		m_cockpit->translate(nosePos);
		m_fuselage->translate(nosePos);
		m_leftEngine->translate(nosePos);
		m_rightEngine->translate(nosePos);
		m_leftNozzle->translate(nosePos);
		m_rightNozzle->translate(nosePos);
		m_leftNozzleGlass->translate(nosePos);
		m_rightNozzleGlass->translate(nosePos);
		m_leftWing->translate(nosePos);
		m_rightWing->translate(nosePos);
		m_leftVStab->translate(nosePos);
		m_rightVStab->translate(nosePos);
		m_leftElevator->translate(nosePos);
		m_rightElevator->translate(nosePos);
		m_leftRudder->translate(nosePos);
		m_rightRudder->translate(nosePos);
		m_leftAileron->translate(nosePos);
		m_rightAileron->translate(nosePos);
	}

	void JW1::updateShaders()
	{ }

	void JW1::render() const
	{
		ShaderPrograms::surface->use();
		renderSurfaces();

		ShaderPrograms::light->use();
		renderLights();
	}

	void JW1::setCtrl(const Common::AirplaneCtrl& airplaneCtrl)
	{
		m_leftElevator->resetRotation();
		m_leftElevator->rotatePitch(-airplaneCtrl.elevatorAngleRad);
		m_rightElevator->resetRotation();
		m_rightElevator->rotatePitch(-airplaneCtrl.elevatorAngleRad);

		static const glm::vec3 rudderAxis = glm::normalize(glm::vec3{0, 654, 261});
		m_leftRudder->resetRotation();
		m_leftRudder->rotate(rudderAxis, airplaneCtrl.rudderAngleRad);
		m_rightRudder->resetRotation();
		m_rightRudder->rotate(rudderAxis, airplaneCtrl.rudderAngleRad);

		static const glm::vec3 rightElevatorAxis = glm::normalize(glm::vec3{888, -45, 297});
		static const glm::vec3 leftElevatorAxis = glm::normalize(glm::vec3{-888, -45, 297});
		m_leftAileron->resetRotation();
		m_leftAileron->rotate(leftElevatorAxis, -airplaneCtrl.aileronsAngleRad);
		m_rightAileron->resetRotation();
		m_rightAileron->rotate(rightElevatorAxis, -airplaneCtrl.aileronsAngleRad);

		static constexpr glm::vec3 nozzleMaxColor{1, 0.8f, 0};
		Material nozzleGlass{airplaneCtrl.thrustRelative * nozzleMaxColor, 1, 1, 1, false};
		m_leftNozzleGlass->setMaterial(nozzleGlass);
		m_rightNozzleGlass->setMaterial(nozzleGlass);
	}

	void JW1::setHP(int hp)
	{
		static const Material red{glm::vec3{1, 0, 0}, 1, 0, 1, false};
		if (!m_isDestroyed && hp == 0)
		{
			m_cone->setMaterial(red);
			m_gun->setMaterial(red);
			m_cockpit->setMaterial(red);
			m_fuselage->setMaterial(red);
			m_leftEngine->setMaterial(red);
			m_rightEngine->setMaterial(red);
			m_leftNozzle->setMaterial(red);
			m_rightNozzle->setMaterial(red);
			m_leftWing->setMaterial(red);
			m_rightWing->setMaterial(red);
			m_leftVStab->setMaterial(red);
			m_rightVStab->setMaterial(red);
			m_leftElevator->setMaterial(red);
			m_rightElevator->setMaterial(red);
			m_leftRudder->setMaterial(red);
			m_rightRudder->setMaterial(red);
			m_leftAileron->setMaterial(red);
			m_rightAileron->setMaterial(red);
			m_isDestroyed = true;
		}
		else if (m_isDestroyed && hp > 0)
		{
			m_cone->setMaterial(texturedMetal);
			m_gun->setMaterial(texturedMetal);
			m_cockpit->setMaterial(blackGlass);
			m_fuselage->setMaterial(texturedMetal);
			m_leftEngine->setMaterial(texturedMetal);
			m_rightEngine->setMaterial(texturedMetal);
			m_leftNozzle->setMaterial(darkMetal);
			m_rightNozzle->setMaterial(darkMetal);
			m_leftWing->setMaterial(texturedMetal);
			m_rightWing->setMaterial(texturedMetal);
			m_leftVStab->setMaterial(texturedMetal);
			m_rightVStab->setMaterial(texturedMetal);
			m_leftElevator->setMaterial(texturedMetal);
			m_rightElevator->setMaterial(texturedMetal);
			m_leftRudder->setMaterial(texturedMetal);
			m_rightRudder->setMaterial(texturedMetal);
			m_leftAileron->setMaterial(texturedMetal);
			m_rightAileron->setMaterial(texturedMetal);
			m_isDestroyed = false;
		}
		Airplane::setHP(hp);
	}

	void JW1::renderSurfaces() const
	{
		m_cone->render(getMatrix());
		m_gun->render(getMatrix());
		m_cockpit->render(getMatrix());
		m_fuselage->render(getMatrix());
		m_leftEngine->render(getMatrix());
		m_rightEngine->render(getMatrix());
		m_leftNozzle->render(getMatrix());
		m_rightNozzle->render(getMatrix());
		m_leftWing->render(getMatrix());
		m_rightWing->render(getMatrix());
		m_leftVStab->render(getMatrix());
		m_rightVStab->render(getMatrix());
		m_leftElevator->render(getMatrix());
		m_rightElevator->render(getMatrix());
		m_leftRudder->render(getMatrix());
		m_rightRudder->render(getMatrix());
		m_leftAileron->render(getMatrix());
		m_rightAileron->render(getMatrix());
	}

	void JW1::renderLights() const
	{
		m_leftNozzleGlass->render(getMatrix());
		m_rightNozzleGlass->render(getMatrix());
	}
}
