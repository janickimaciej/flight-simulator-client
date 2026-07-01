#include "graphics/meshes/mapGenerator.hpp"

#include "common/terrains/maps/map.hpp"
#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <array>
#include <vector>

namespace Graphics
{
	std::vector<Vertex> MapGenerator::generate(const Common::Terrains::Map& terrain)
	{
		float lengthX = terrain.getLengthX();
		float lengthZ = terrain.getLengthZ();
		float spacingX = terrain.getSpacingX();
		float spacingZ = terrain.getSpacingZ();
		int cellCountX = static_cast<int>(lengthX / spacingX) - 1;
		int cellCountZ = static_cast<int>(lengthZ / spacingZ) - 1;

		std::vector<Vertex> vertices{};

		for (int i = 0; i < cellCountX; ++i)
		{
			for (int j = 0; j < cellCountZ; ++j)
			{
				static constexpr int cellsToTexturesRatio = 10;
				static constexpr float textureScaling = 1.0f / cellsToTexturesRatio;
				float lowXTexturePos = (i % cellsToTexturesRatio) * textureScaling;
				float highXTexturePos = lowXTexturePos + textureScaling;
				float lowZTexturePos = (j % cellsToTexturesRatio) * textureScaling;
				float highZTexturePos = lowZTexturePos + textureScaling;

				std::array<Vertex, 3> triangle1{};
				std::array<Vertex, 3> triangle2{};

				triangle1[0].pos = calcPos(i * spacingX, j * spacingZ, terrain);
				triangle1[0].texturePos = glm::vec2{lowXTexturePos, lowZTexturePos};
				triangle1[0].normalVector = calcNormalVector(i * spacingX, j * spacingZ,
					terrain);

				triangle1[1].pos = calcPos((i + 1) * spacingX, (j + 1) * spacingZ,
					terrain);
				triangle1[1].texturePos =
					glm::vec2{highXTexturePos, highZTexturePos};
				triangle1[1].normalVector = calcNormalVector((i + 1) * spacingX, (j + 1) * spacingZ,
					terrain);

				triangle1[2].pos = calcPos((i + 1) * spacingX, j * spacingZ, terrain);
				triangle1[2].texturePos = glm::vec2{highXTexturePos, lowZTexturePos};
				triangle1[2].normalVector = calcNormalVector((i + 1) * spacingX, j * spacingZ,
					terrain);

				vertices.push_back(triangle1[0]);
				vertices.push_back(triangle1[1]);
				vertices.push_back(triangle1[2]);

				triangle2[0].pos = calcPos(i * spacingX, j * spacingZ, terrain);
				triangle2[0].texturePos = glm::vec2{lowXTexturePos, lowZTexturePos};
				triangle2[0].normalVector = calcNormalVector(i * spacingX, j * spacingZ, terrain);

				triangle2[1].pos = calcPos(i * spacingX, (j + 1) * spacingZ, terrain);
				triangle2[1].texturePos = glm::vec2{lowXTexturePos, highZTexturePos};
				triangle2[1].normalVector = calcNormalVector(i * spacingX, (j + 1) * spacingZ,
					terrain);

				triangle2[2].pos = calcPos((i + 1) * spacingX, (j + 1) * spacingZ, terrain);
				triangle2[2].texturePos = glm::vec2{highXTexturePos, highZTexturePos};
				triangle2[2].normalVector = calcNormalVector((i + 1) * spacingX, (j + 1) * spacingZ,
					terrain);

				vertices.push_back(triangle2[0]);
				vertices.push_back(triangle2[1]);
				vertices.push_back(triangle2[2]);
			}
		}

		return vertices;
	}

	glm::vec3 MapGenerator::calcPos(float x, float z, const Common::Terrains::Map& map)
	{
		return glm::vec3{x, map.height(x, z), z};
	}

	glm::vec3 MapGenerator::calcNormalVector(float x, float z, const Common::Terrains::Map& map)
	{
		return glm::normalize(glm::vec3{-map.heightDerivX(x, z), 1, -map.heightDerivZ(x, z)});
	}
}
