#include "graphics/textField.hpp"

#include "graphics/assetManager.hpp"
#include "graphics/config.hpp"
#include "graphics/material.hpp"
#include "graphics/path.hpp"
#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	const std::string modelName = "characters";

	TextField::TextField(const std::string& text, const glm::vec3& offset, float scaleRatio)
	{
		auto& proceduralMeshManager = AssetManager<ProceduralMeshName, const Mesh>::instance();
		auto& textureManager = AssetManager<std::string, const Texture>::instance();

		const Material billboard{glm::vec3{1, 1, 1}, 1, 1, 1, false};
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
			submodel.translate(offset);
			submodel.translate(glm::vec3{static_cast<int>(i) * scaleRatio * characterWidth, 0, 0});
			submodel.scale(scaleRatio);
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
