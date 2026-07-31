#include "graphics/textField.hpp"

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

	TextField::TextField(const std::string& text, const glm::vec3& pos, float scaleRatio)
	{
		auto& proceduralMeshManager = AssetManager<ProceduralMeshName, const Mesh>::instance();
		auto& textureManager = AssetManager<std::string, const Texture>::instance();

		const Material billboard{glm::vec3{1, 1, 1}, 1, 1, 1, false};
		glm::vec2 scaledCharacterSize = scaleRatio * characterSize;
		float textWidthHalf = text.size() * scaledCharacterSize.x / 2.0f;
		glm::vec3 firstCharacterPos = pos +
			glm::vec3{-textWidthHalf + scaledCharacterSize.x / 2.0f, 0, 0};
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

			submodel.scale(scaleRatio);
			glm::vec3 characterPos = firstCharacterPos +
				glm::vec3{static_cast<int>(i) * scaledCharacterSize.x, 0, 0};
			submodel.translate(characterPos);

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

	void TextField::render(const glm::mat4& modelMatrix) const
	{
		for (const Submodel& submodel : m_textSubmodels)
		{
			submodel.render(modelMatrix);
		}
	}
}
