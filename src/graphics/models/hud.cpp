#include "graphics/models/hud.hpp"

#include "common/state.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderPrograms.hpp"
#include "graphics/time.hpp"

#include <glm/glm.hpp>

#include <cmath>
#include <cstddef>
#include <string>

namespace Graphics
{
	static constexpr float smallFontSize = 0.0003f;
	static constexpr float largeFontSize = 0.0006f;
	static constexpr float bottomLineLargeFontY = -0.048f;
	static constexpr float bottomLineSmallFontY = -0.055f;
	static constexpr float indicatorsY = -0.435f;
	static constexpr glm::vec3 fpsPos{-0.97f, 0.50f, 0};
	static constexpr glm::vec3 playerCountPos{0.875f, 0.50f, 0};
	static constexpr glm::vec3 altitudePos{-0.85f, indicatorsY, 0};
	static constexpr glm::vec3 radarAltitudePos{-0.44f, indicatorsY, 0};
	static constexpr glm::vec3 hpPos{0, indicatorsY, 0};
	static constexpr glm::vec3 verticalSpeedPos{0.44f, indicatorsY, 0};
	static constexpr glm::vec3 airspeedPos{0.85f, indicatorsY, 0};

	HUD::HUD()
	{
		m_fpsNumber = std::make_unique<TextField>("___", fpsPos, smallFontSize);
		m_fpsUnit = std::make_unique<TextField>("FPS", fpsPos + glm::vec3{0.05f, 0, 0},
			smallFontSize);

		m_playerCountNumber = std::make_unique<TextField>("__", playerCountPos, smallFontSize);
		m_playerCountUnit = std::make_unique<TextField>("PLAYERS",
			playerCountPos + glm::vec3{0.07f, 0, 0}, smallFontSize);

		m_altitudeText = std::make_unique<TextField>("ALTITUDE", altitudePos, smallFontSize);
		m_altitudeNumber = std::make_unique<TextField>("______",
			altitudePos + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize);
		m_altitudeUnit = std::make_unique<TextField>("M",
			altitudePos + glm::vec3{0.097f, bottomLineSmallFontY, 0}, smallFontSize);

		m_radarAltitudeText = std::make_unique<TextField>("RADAR_ALTITUDE", radarAltitudePos,
			smallFontSize);
		m_radarAltitudeNumber = std::make_unique<TextField>("_____",
			radarAltitudePos + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize);
		m_radarAltitudeUnit = std::make_unique<TextField>("M",
			radarAltitudePos + glm::vec3{0.085f, bottomLineSmallFontY, 0}, smallFontSize);

		m_hpNumber = std::make_unique<TextField>("___",
			hpPos + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize);
		m_hpUnit = std::make_unique<TextField>("HP",
			hpPos + glm::vec3{0.065f, bottomLineSmallFontY, 0}, smallFontSize);

		m_verticalSpeedText = std::make_unique<TextField>("VERTICAL_SPEED", verticalSpeedPos,
			smallFontSize);
		m_verticalSpeedNumber = std::make_unique<TextField>("_____",
			verticalSpeedPos + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize);
		m_verticalSpeedUnit = std::make_unique<TextField>("MPS",
			verticalSpeedPos + glm::vec3{0.097f, bottomLineSmallFontY, 0}, smallFontSize);

		m_airspeedText = std::make_unique<TextField>("AIRSPEED", airspeedPos, smallFontSize);
		m_airspeedNumber = std::make_unique<TextField>("____",
			airspeedPos + glm::vec3{0, bottomLineLargeFontY, 0}, largeFontSize);
		m_airspeedUnit = std::make_unique<TextField>("KPH",
			airspeedPos + glm::vec3{0.082f, bottomLineSmallFontY, 0}, smallFontSize);

		auto& textureManager = AssetManager<std::string, const Texture>::instance();
		for (char i = '0'; i <= '9'; ++i)
		{
			m_textureLocks.push_back(textureManager.get(
				Texture::getId(texturePath("characters", std::string{i}),
				Texture::Wrapping::clampToEdge, Texture::Wrapping::clampToEdge)));
		}
		m_textureLocks.push_back(textureManager.get(
			Texture::getId(texturePath("characters", "-"), Texture::Wrapping::clampToEdge,
			Texture::Wrapping::clampToEdge)));
	}

	void HUD::updateShaders()
	{ }

	void HUD::render() const
	{
		ShaderPrograms::hud->use();
		renderHUD();
	}

	void HUD::update(const Airplane& ownAirplane, const Map& map, int playerCount)
	{
		m_lastUpdateTime += Time::getDeltaTime();
		static constexpr float refreshTime = 0.5f;
		if (m_lastUpdateTime >= refreshTime)
		{
			Common::State state = ownAirplane.getState();
			int fps = Time::getFPS();
			refresh(*m_fpsNumber, fps, 3, false);
			refresh(*m_playerCountNumber, playerCount, 2, false);
			m_playerCountUnit->setCharacter(6, playerCount == 1 ? '_' : 'S');
			refresh(*m_altitudeNumber, static_cast<int>(state.pos.y), 5, true);
			refresh(*m_radarAltitudeNumber, static_cast<int>(state.pos.y -
				map.getHeight(state.pos.x, state.pos.z)), 5, false);
			refresh(*m_hpNumber, ownAirplane.getHP(), 3, false);
			refresh(*m_verticalSpeedNumber,
				static_cast<int>((state.orientation * state.velocity).y), 4, true);
			refresh(*m_airspeedNumber, static_cast<int>(3.6f * glm::length(state.velocity)), 4,
				false);
			m_lastUpdateTime = 0;
		}
	}

	void HUD::renderHUD() const
	{
		glm::mat4 modelMatrix = getMatrix();

		m_fpsNumber->render(modelMatrix);
		m_fpsUnit->render(modelMatrix);

		m_playerCountNumber->render(modelMatrix);
		m_playerCountUnit->render(modelMatrix);

		m_altitudeText->render(modelMatrix);
		m_altitudeNumber->render(modelMatrix);
		m_altitudeUnit->render(modelMatrix);

		m_radarAltitudeText->render(modelMatrix);
		m_radarAltitudeNumber->render(modelMatrix);
		m_radarAltitudeUnit->render(modelMatrix);

		m_hpNumber->render(modelMatrix);
		m_hpUnit->render(modelMatrix);

		m_verticalSpeedText->render(modelMatrix);
		m_verticalSpeedNumber->render(modelMatrix);
		m_verticalSpeedUnit->render(modelMatrix);

		m_airspeedText->render(modelMatrix);
		m_airspeedNumber->render(modelMatrix);
		m_airspeedUnit->render(modelMatrix);
	}

	void HUD::refresh(TextField& textField, int value, int numberOfDigits, bool isSigned)
	{
		if (isSigned)
		{
			if (value < 0)
			{
				value = -value;
				textField.setCharacter(0, '-');
			}
			else
			{
				textField.setCharacter(0, '_');
			}
		}
		else if (value < 0)
		{
			value = 0;
		}

		int upperBound =
			static_cast<int>(std::round(std::pow(10.0f, static_cast<float>(numberOfDigits)))) - 1;
		if (value > upperBound)
		{
			value = upperBound;
		}

		std::string text = std::to_string(value);
		std::size_t offset = numberOfDigits - text.size();
		for (std::size_t i = 0; i < offset; ++i)
		{
			textField.setCharacter(isSigned ? i + 1 : i, '_');
		}
		for (std::size_t i = 0; i < text.size(); ++i)
		{
			textField.setCharacter(isSigned ? i + 1 + offset : i + offset, text[i]);
		}
	}
}
