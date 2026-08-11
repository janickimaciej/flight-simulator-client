#include "graphics/meshes/meshGenerator.hpp"

#include "common/terrains/maps.hpp"
#include "graphics/config.hpp"
#include "graphics/meshes/billboardGenerator.hpp"
#include "graphics/meshes/bulletGenerator.hpp"
#include "graphics/meshes/seaGenerator.hpp"
#include "graphics/meshes/terrainGenerator.hpp"

namespace Graphics
{
	std::vector<Vertex> MeshGenerator::generate(ProceduralMeshName name)
	{
		switch (name)
		{
			case ProceduralMeshName::characterBillboard:
				return BillboardGenerator::generate(characterSize);

			case ProceduralMeshName::bullet:
				return BulletGenerator::generate();

			case ProceduralMeshName::sea:
				return SeaGenerator::generate();

			case ProceduralMeshName::island:
			{
				glm::vec2 size{40000, 40000};
				glm::vec2 spacing{50, 50};
				std::unique_ptr<Common::Terrains::Terrain> terrain =
					Common::Terrains::Maps::island();
				return TerrainGenerator::generate(*terrain, size, spacing);
			}
		}
		return std::vector<Vertex>{};
	}
}
