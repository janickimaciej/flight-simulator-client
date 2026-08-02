#pragma once

#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace Graphics
{
	class TextField : public Model
	{
	public:
		TextField(const std::string& text);

		void setCharacter(std::size_t index, char character);

		virtual void updateShaders() override;
		virtual void render() const override;

		float getLeftBorderPos() const;
		void setLeftBorderPos(float pos);
		float getRightBorderPos() const;
		void setRightBorderPos(float pos);
		float getBottomBorderPos() const;
		void setBottomBorderPos(float pos);
		float getTopBorderPos() const;
		void setTopBorderPos(float pos);

	private:
		std::vector<Submodel> m_textSubmodels{};

		float getWidth() const;
		float getHeight() const;
	};
}
