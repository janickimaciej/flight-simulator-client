#include "graphics/meshes/meshGenerator.hpp"

#include "common/terrains/maps.hpp"
#include "graphics/config.hpp"
#include "graphics/meshes/bulletGenerator.hpp"
#include "graphics/meshes/quadGenerator.hpp"
#include "graphics/meshes/terrainGenerator.hpp"

namespace Graphics
{
	std::vector<Vertex> MeshGenerator::generate(ProceduralMeshName name)
	{
		switch (name)
		{
			case ProceduralMeshName::bullet:
				return BulletGenerator::generate();

			case ProceduralMeshName::characterBillboard:
				return QuadGenerator::generate(characterSize, true);

			case ProceduralMeshName::island:
			{
				glm::vec2 size{40000, 40000};
				glm::vec2 spacing{50, 50};
				std::unique_ptr<Common::Terrains::Terrain> terrain =
					Common::Terrains::Maps::island();
				return TerrainGenerator::generate(*terrain, size, spacing);
			}

			case ProceduralMeshName::screenQuad:
				return QuadGenerator::generate({2, 2}, false);

			case ProceduralMeshName::sea:
				return QuadGenerator::generate({2 * worldCameraFarPlane, 2 * worldCameraFarPlane},
					false);
		}
		return std::vector<Vertex>{};
	}
}
