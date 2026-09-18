#include "graphics/meshes/terrainGenerator.hpp"

#include <array>
#include <cmath>

namespace Graphics
{
	std::vector<Vertex> TerrainGenerator::generateShore(const Common::Terrains::Terrain& terrain,
		const glm::vec2& size, const glm::vec2& spacing, float waterLevel,
		float waterTransparencyDepth)
	{
		auto triangleAcceptance =
			[waterLevel, waterTransparencyDepth] (const std::array<Vertex, 3>& triangle)
			{
				float minTransparencyLevel = waterLevel - waterTransparencyDepth;
				for (int i = 0; i < 3; ++i)
				{
					if (triangle[i].pos.y >= minTransparencyLevel && triangle[i].pos.y < waterLevel)
					{
						return true;
					}
				}
				return false;
			};
		return generate(terrain, size, spacing, triangleAcceptance);
	}

	std::vector<Vertex> TerrainGenerator::generateLand(const Common::Terrains::Terrain& terrain,
		const glm::vec2& size, const glm::vec2& spacing, float waterLevel)
	{
		auto triangleAcceptance =
			[waterLevel] (const std::array<Vertex, 3>& triangle)
			{
				for (int i = 0; i < 3; ++i)
				{
					if (triangle[i].pos.y < waterLevel)
					{
						return false;
					}
				}
				return true;
			};
		return generate(terrain, size, spacing, triangleAcceptance);
	}

	std::vector<Vertex> TerrainGenerator::generate(const Common::Terrains::Terrain& terrain,
		const glm::vec2& size, const glm::vec2& spacing,
		const std::function<bool(const std::array<Vertex, 3>&)>& triangleAcceptance)
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
				glm::vec2 lowTexturePos = {(i % cellToTextureRatio) * textureScaling,
					(j % cellToTextureRatio) * textureScaling};
				glm::vec2 highTexturePos = lowTexturePos +
					glm::vec2{textureScaling, textureScaling};

				std::array<Vertex, 3> triangle1{};
				triangle1[0] = getVertex(i, j, terrain, size, spacing, lowTexturePos);
				triangle1[1] = getVertex(i + 1, j + 1, terrain, size, spacing, highTexturePos);
				triangle1[2] = getVertex(i + 1, j, terrain, size, spacing,
					{highTexturePos.x, lowTexturePos.y});
				if (triangleAcceptance(triangle1))
				{
					vertices.push_back(triangle1[0]);
					vertices.push_back(triangle1[1]);
					vertices.push_back(triangle1[2]);
				}
				
				std::array<Vertex, 3> triangle2{};
				triangle2[0] = getVertex(i, j, terrain, size, spacing, lowTexturePos);
				triangle2[1] = getVertex(i, j + 1, terrain, size, spacing,
					{lowTexturePos.x, highTexturePos.y});
				triangle2[2] = getVertex(i + 1, j + 1, terrain, size, spacing, highTexturePos);
				if (triangleAcceptance(triangle2))
				{
					vertices.push_back(triangle2[0]);
					vertices.push_back(triangle2[1]);
					vertices.push_back(triangle2[2]);
				}
			}
		}

		return vertices;
	}

	glm::vec3 TerrainGenerator::getPos(int xIndex, int zIndex,
		const Common::Terrains::Terrain& terrain, const glm::vec2& size, const glm::vec2& spacing)
	{
		float x = -size.x / 2.0f + xIndex * spacing.x;
		float z = -size.y / 2.0f + zIndex * spacing.y;
		return glm::vec3{x, terrain.height(x, z), z};
	}

	glm::vec3 TerrainGenerator::getNormalVector(int xIndex, int zIndex,
		const Common::Terrains::Terrain& terrain, const glm::vec2& size, const glm::vec2& spacing)
	{
		float x = -size.x / 2.0f + xIndex * spacing.x;
		float z = -size.y / 2.0f + zIndex * spacing.y;
		return glm::normalize(glm::vec3{-terrain.heightDerivX(x, z), 1,
			-terrain.heightDerivZ(x, z)});
	}

	Vertex TerrainGenerator::getVertex(int xIndex, int zIndex,
		const Common::Terrains::Terrain& terrain, const glm::vec2& size, const glm::vec2& spacing,
		const glm::vec2& texturePos)
	{
		Vertex vertex{};
		vertex.pos = getPos(xIndex, zIndex, terrain, size, spacing);
		vertex.texturePos = texturePos;
		vertex.normalVector = getNormalVector(xIndex, zIndex, terrain, size, spacing);
		return vertex;
	}
}
