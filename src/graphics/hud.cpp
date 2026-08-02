#include "graphics/hud.hpp"

#include "common/state.hpp"
#include "graphics/assetManager.hpp"
#include "graphics/config.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderPrograms.hpp"
#include "graphics/time.hpp"

#include <glm/glm.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <string>

namespace Graphics
{
	HUD::HUD()
	{
		m_fpsNumber = std::make_unique<TextField>("___");
		m_fpsUnit = std::make_unique<TextField>("FPS");

		m_playerCountNumber = std::make_unique<TextField>("__");
		m_playerCountUnit = std::make_unique<TextField>("PLAYERS");

		m_altitudeText = std::make_unique<TextField>("ALTITUDE");
		m_altitudeNumber = std::make_unique<TextField>("______");
		m_altitudeUnit = std::make_unique<TextField>("M");

		m_radarAltitudeText = std::make_unique<TextField>("RADAR_ALTITUDE");
		m_radarAltitudeNumber = std::make_unique<TextField>("_____");
		m_radarAltitudeUnit = std::make_unique<TextField>("M");

		m_hpNumber = std::make_unique<TextField>("___");
		m_hpUnit = std::make_unique<TextField>("HP");

		m_verticalSpeedText = std::make_unique<TextField>("VERTICAL_SPEED");
		m_verticalSpeedNumber = std::make_unique<TextField>("_____");
		m_verticalSpeedUnit = std::make_unique<TextField>("MPS");

		m_airspeedText = std::make_unique<TextField>("AIRSPEED");
		m_airspeedNumber = std::make_unique<TextField>("____");
		m_airspeedUnit = std::make_unique<TextField>("KPH");

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

	void HUD::updateLayout(float aspectRatio)
	{
		if (aspectRatio == m_prevAspectRatio) return;
		m_prevAspectRatio = aspectRatio;

		float rightBorder = 1.0f;
		float topBorder = rightBorder / aspectRatio;
		float leftBorder = -rightBorder;
		float bottomBorder = -topBorder;

		float smallerDimension = std::min(rightBorder - leftBorder, topBorder - bottomBorder);

		static constexpr float largeFontRelativeSize = 0.0005f;
		float largeFontSize = largeFontRelativeSize * smallerDimension;
		static constexpr float smallFontRelativeSize = largeFontRelativeSize / 2.0f;
		float smallFontSize = smallFontRelativeSize * smallerDimension;

		m_fpsNumber->setScale(smallFontSize);
		m_fpsUnit->setScale(smallFontSize);

		m_playerCountNumber->setScale(smallFontSize);
		m_playerCountUnit->setScale(smallFontSize);

		m_altitudeText->setScale(smallFontSize);
		m_altitudeNumber->setScale(largeFontSize);
		m_altitudeUnit->setScale(smallFontSize);

		m_radarAltitudeText->setScale(smallFontSize);
		m_radarAltitudeNumber->setScale(largeFontSize);
		m_radarAltitudeUnit->setScale(smallFontSize);

		m_hpNumber->setScale(largeFontSize);
		m_hpUnit->setScale(smallFontSize);

		m_verticalSpeedText->setScale(smallFontSize);
		m_verticalSpeedNumber->setScale(largeFontSize);
		m_verticalSpeedUnit->setScale(smallFontSize);

		m_airspeedText->setScale(smallFontSize);
		m_airspeedNumber->setScale(largeFontSize);
		m_airspeedUnit->setScale(smallFontSize);

		glm::vec2 smallCharacterSize = smallFontSize * characterSize;
		glm::vec2 largeCharacterSize = largeFontSize * characterSize;
		static constexpr float largeFontBaseRelativeOffset = 0.1f;
		float largeFontBaseOffset = largeFontBaseRelativeOffset * largeCharacterSize.y;

		m_fpsNumber->setLeftBorderPos(leftBorder + smallCharacterSize.y);
		m_fpsUnit->setLeftBorderPos(m_fpsNumber->getRightBorderPos() + smallCharacterSize.x);
		m_fpsNumber->setTopBorderPos(topBorder - smallCharacterSize.y);
		m_fpsUnit->setTopBorderPos(m_fpsNumber->getTopBorderPos());

		m_playerCountUnit->setRightBorderPos(rightBorder - smallCharacterSize.y);
		m_playerCountNumber->setRightBorderPos(m_playerCountUnit->getLeftBorderPos() -
			smallCharacterSize.x);
		m_playerCountUnit->setTopBorderPos(topBorder - smallCharacterSize.y);
		m_playerCountNumber->setTopBorderPos(m_playerCountUnit->getTopBorderPos());

		float textYOffset = smallCharacterSize.x;

		m_altitudeNumber->setLeftBorderPos(leftBorder + largeCharacterSize.y);
		m_altitudeUnit->setLeftBorderPos(m_altitudeNumber->getRightBorderPos() +
			smallCharacterSize.x);
		m_altitudeText->setRightBorderPos(m_altitudeNumber->getRightBorderPos());
		m_altitudeNumber->setBottomBorderPos(bottomBorder + largeCharacterSize.y);
		m_altitudeUnit->setBottomBorderPos(m_altitudeNumber->getBottomBorderPos() +
			largeFontBaseOffset);
		m_altitudeText->setBottomBorderPos(m_altitudeNumber->getTopBorderPos() + textYOffset);

		m_hpNumber->setPos({});
		m_hpUnit->setLeftBorderPos(m_hpNumber->getRightBorderPos() + smallCharacterSize.x);
		m_hpNumber->setBottomBorderPos(bottomBorder + largeCharacterSize.y);
		m_hpUnit->setBottomBorderPos(m_hpNumber->getBottomBorderPos() + largeFontBaseOffset);

		m_airspeedUnit->setRightBorderPos(rightBorder - largeCharacterSize.y);
		m_airspeedNumber->setRightBorderPos(m_airspeedUnit->getLeftBorderPos() -
			smallCharacterSize.x);
		m_airspeedText->setRightBorderPos(m_airspeedNumber->getRightBorderPos());
		m_airspeedNumber->setBottomBorderPos(bottomBorder + largeCharacterSize.y);
		m_airspeedUnit->setBottomBorderPos(m_airspeedNumber->getBottomBorderPos() +
			largeFontBaseOffset);
		m_airspeedText->setBottomBorderPos(m_airspeedNumber->getTopBorderPos() + textYOffset);

		m_radarAltitudeNumber->setPos(m_altitudeNumber->getPos() / 2.0f);
		m_radarAltitudeUnit->setLeftBorderPos(m_radarAltitudeNumber->getRightBorderPos() +
			smallCharacterSize.x);
		m_radarAltitudeText->setRightBorderPos(m_radarAltitudeNumber->getRightBorderPos());
		m_radarAltitudeNumber->setBottomBorderPos(bottomBorder + largeCharacterSize.y);
		m_radarAltitudeUnit->setBottomBorderPos(m_radarAltitudeNumber->getBottomBorderPos() +
			largeFontBaseOffset);
		m_radarAltitudeText->setBottomBorderPos(m_radarAltitudeNumber->getTopBorderPos() +
			textYOffset);

		m_verticalSpeedNumber->setPos(m_airspeedNumber->getPos() / 2.0f);
		m_verticalSpeedUnit->setLeftBorderPos(m_verticalSpeedNumber->getRightBorderPos() +
			smallCharacterSize.x);
		m_verticalSpeedText->setRightBorderPos(m_verticalSpeedNumber->getRightBorderPos());
		m_verticalSpeedNumber->setBottomBorderPos(bottomBorder + largeCharacterSize.y);
		m_verticalSpeedUnit->setBottomBorderPos(m_verticalSpeedNumber->getBottomBorderPos() +
			largeFontBaseOffset);
		m_verticalSpeedText->setBottomBorderPos(m_verticalSpeedNumber->getTopBorderPos() +
			textYOffset);
	}

	void HUD::render() const
	{
		ShaderPrograms::hud->use();

		m_fpsNumber->render();
		m_fpsUnit->render();

		m_playerCountNumber->render();
		m_playerCountUnit->render();

		m_altitudeText->render();
		m_altitudeNumber->render();
		m_altitudeUnit->render();

		m_radarAltitudeText->render();
		m_radarAltitudeNumber->render();
		m_radarAltitudeUnit->render();

		m_hpNumber->render();
		m_hpUnit->render();

		m_verticalSpeedText->render();
		m_verticalSpeedNumber->render();
		m_verticalSpeedUnit->render();

		m_airspeedText->render();
		m_airspeedNumber->render();
		m_airspeedUnit->render();
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
