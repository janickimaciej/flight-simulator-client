#include "graphics/meshes/mapGenerator.hpp"

#include <array>
#include <cmath>

namespace Graphics
{
	std::vector<Vertex> MapGenerator::generate(const Common::Terrains::Terrain& terrain,
		const glm::vec2& size, const glm::vec2& spacing)
	{
		int cellCountX = static_cast<int>(std::round(size.x / spacing.x));
		int cellCountZ = static_cast<int>(std::round(size.y / spacing.y));

		std::vector<Vertex> vertices{};

		for (int i = 0; i < cellCountX; ++i)
		{
			for (int j = 0; j < cellCountZ; ++j)
			{
				static constexpr int cellToTextureRatio = 10;
				static constexpr float textureScaling = 1.0f / cellToTextureRatio;
				float lowXTexturePos = (i % cellToTextureRatio) * textureScaling;
				float highXTexturePos = lowXTexturePos + textureScaling;
				float lowZTexturePos = (j % cellToTextureRatio) * textureScaling;
				float highZTexturePos = lowZTexturePos + textureScaling;

				std::array<Vertex, 3> triangle1{};
				std::array<Vertex, 3> triangle2{};

				triangle1[0].pos = calcPos(i, j, terrain, size, spacing);
				triangle1[0].texturePos = glm::vec2{lowXTexturePos, lowZTexturePos};
				triangle1[0].normalVector = calcNormalVector(i, j, terrain, size, spacing);

				triangle1[1].pos = calcPos(i + 1, j + 1, terrain, size, spacing);
				triangle1[1].texturePos = glm::vec2{highXTexturePos, highZTexturePos};
				triangle1[1].normalVector = calcNormalVector(i + 1, j + 1, terrain, size, spacing);

				triangle1[2].pos = calcPos(i + 1, j, terrain, size, spacing);
				triangle1[2].texturePos = glm::vec2{highXTexturePos, lowZTexturePos};
				triangle1[2].normalVector = calcNormalVector(i + 1, j, terrain, size, spacing);

				if (triangle1[0].pos.y >= 0 || triangle1[1].pos.y >= 0 || triangle1[2].pos.y >= 0)
				{
					vertices.push_back(triangle1[0]);
					vertices.push_back(triangle1[1]);
					vertices.push_back(triangle1[2]);
				}

				triangle2[0].pos = calcPos(i, j, terrain, size, spacing);
				triangle2[0].texturePos = glm::vec2{lowXTexturePos, lowZTexturePos};
				triangle2[0].normalVector = calcNormalVector(i, j, terrain, size, spacing);

				triangle2[1].pos = calcPos(i, j + 1, terrain, size, spacing);
				triangle2[1].texturePos = glm::vec2{lowXTexturePos, highZTexturePos};
				triangle2[1].normalVector = calcNormalVector(i, j + 1, terrain, size, spacing);

				triangle2[2].pos = calcPos(i + 1, j + 1, terrain, size, spacing);
				triangle2[2].texturePos = glm::vec2{highXTexturePos, highZTexturePos};
				triangle2[2].normalVector = calcNormalVector(i + 1, j + 1, terrain, size, spacing);

				if (triangle2[0].pos.y >= 0 || triangle2[1].pos.y >= 0 || triangle2[2].pos.y >= 0)
				{
					vertices.push_back(triangle2[0]);
					vertices.push_back(triangle2[1]);
					vertices.push_back(triangle2[2]);
				}
			}
		}

		return vertices;
	}

	glm::vec3 MapGenerator::calcPos(int xIndex, int zIndex,
		const Common::Terrains::Terrain& terrain, const glm::vec2& size, const glm::vec2& spacing)
	{
		float x = -size.x / 2.0f + xIndex * spacing.x;
		float z = -size.y / 2.0f + zIndex * spacing.y;
		return glm::vec3{x, terrain.height(x, z), z};
	}

	glm::vec3 MapGenerator::calcNormalVector(int xIndex, int zIndex,
		const Common::Terrains::Terrain& terrain, const glm::vec2& size, const glm::vec2& spacing)
	{
		float x = -size.x / 2.0f + xIndex * spacing.x;
		float z = -size.y / 2.0f + zIndex * spacing.y;
		return glm::normalize(glm::vec3{-terrain.heightDerivX(x, z), 1,
			-terrain.heightDerivZ(x, z)});
	}
}
