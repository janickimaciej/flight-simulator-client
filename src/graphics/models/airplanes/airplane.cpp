#include "graphics/models/airplanes/airplane.hpp"

#include "graphics/models/airplanes/jw1.hpp"
#include "graphics/models/airplanes/mustang.hpp"
#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	std::unique_ptr<Airplane> Airplane::createAirplane(Common::AirplaneType airplaneType)
	{
		switch (airplaneType)
		{
			case Common::AirplaneType::mustang:
				return std::make_unique<Mustang>();

			case Common::AirplaneType::jw1:
				return std::make_unique<JW1>();
		}
		return nullptr;
	}

	void Airplane::render() const
	{
		glm::mat4 modelMatrix = getMatrix();

		ShaderPrograms::surface->use();
		renderSurfaces(modelMatrix);

		ShaderPrograms::light->use();
		renderLights(modelMatrix);
	}

	void Airplane::renderLocally() const
	{
		glm::mat4 modelMatrix{1};

		ShaderPrograms::surface->use();
		renderSurfaces(modelMatrix);

		ShaderPrograms::light->use();
		renderLights(modelMatrix);
	}

	int Airplane::getHP() const
	{
		return m_hp;
	}

	void Airplane::setHP(int hp)
	{
		m_hp = hp;
	}
}
