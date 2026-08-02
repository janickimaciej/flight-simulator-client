#include "graphics/models/textField.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/config.hpp"
#include "graphics/material.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderPrograms.hpp"
#include "graphics/texture.hpp"

namespace Graphics
{
	const std::string modelName = "characters";

	TextField::TextField(const std::string& text)
	{
		auto& proceduralMeshManager = AssetManager<ProceduralMeshName, const Mesh>::instance();
		auto& textureManager = AssetManager<std::string, const Texture>::instance();

		const Material billboard{glm::vec3{1, 1, 1}, 1, 1, 1, false};
		float textWidthHalf = text.size() * characterSize.x / 2.0f;
		glm::vec3 firstCharacterPos = glm::vec3{-textWidthHalf + characterSize.x / 2.0f, 0, 0};
		for (std::size_t i = 0; i < text.size(); ++i)
		{
			Submodel submodel
			{
					*ShaderPrograms::hud,
					proceduralMeshManager.get(ProceduralMeshName::characterBillboard),
					billboard,
					textureManager.get(Texture::getId(texturePath(modelName, std::string{text[i]}),
						Texture::Wrapping::clampToEdge, Texture::Wrapping::clampToEdge))
			};

			glm::vec3 characterPos = firstCharacterPos +
				glm::vec3{static_cast<int>(i) * characterSize.x, 0, 0};
			submodel.setPos(characterPos);

			m_textSubmodels.push_back(submodel);
		}
	}

	void TextField::setCharacter(std::size_t index, char character)
	{
		if (index < 0 || index >= m_textSubmodels.size())
		{
			return;
		}
		auto& textureManager = AssetManager<std::string, const Texture>::instance();
		m_textSubmodels[index].setTexture(textureManager.get(
			Texture::getId(texturePath(modelName, std::string{character}),
			Texture::Wrapping::clampToEdge, Texture::Wrapping::clampToEdge)));
	}

	void TextField::updateShaders()
	{ }

	void TextField::render() const
	{
		glm::mat4 modelMatrix = getMatrix();

		for (const Submodel& submodel : m_textSubmodels)
		{
			submodel.render(modelMatrix);
		}
	}

	float TextField::getLeftBorderPos() const
	{
		return getPos().x - getWidth() / 2.0f;
	}

	void TextField::setLeftBorderPos(float pos)
	{
		glm::vec3 fullPos = getPos();
		fullPos.x = pos + getWidth() / 2.0f;
		setPos(fullPos);
	}

	float TextField::getRightBorderPos() const
	{
		return getPos().x + getWidth() / 2.0f;
	}

	void TextField::setRightBorderPos(float pos)
	{
		glm::vec3 fullPos = getPos();
		fullPos.x = pos - getWidth() / 2.0f;
		setPos(fullPos);
	}

	float TextField::getBottomBorderPos() const
	{
		return getPos().y - getHeight() / 2.0f;
	}

	void TextField::setBottomBorderPos(float pos)
	{
		glm::vec3 fullPos = getPos();
		fullPos.y = pos + getHeight() / 2.0f;
		setPos(fullPos);
	}

	float TextField::getTopBorderPos() const
	{
		return getPos().y + getHeight() / 2.0f;
	}

	void TextField::setTopBorderPos(float pos)
	{
		glm::vec3 fullPos = getPos();
		fullPos.y = pos - getHeight() / 2.0f;
		setPos(fullPos);
	}

	float TextField::getWidth() const
	{
		return m_textSubmodels.size() * getScale() * characterSize.x;
	}

	float TextField::getHeight() const
	{
		return getScale() * characterSize.y;
	}
}
