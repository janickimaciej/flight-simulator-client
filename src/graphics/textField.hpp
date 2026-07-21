#pragma once

#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/submodels/submodel.hpp"

#include <glm/glm.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace Graphics
{
	class TextField
	{
	public:
		TextField(const std::string& text, const glm::vec3& offset, float scaleRatio);
		void setCharacter(std::size_t index, char character);
		void render(const glm::mat4& modelMatrix) const;

	private:
		std::vector<Submodel> m_textSubmodels{};
	};
}
