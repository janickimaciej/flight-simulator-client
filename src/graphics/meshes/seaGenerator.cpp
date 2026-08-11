#include "graphics/meshes/seaGenerator.hpp"

#include "graphics/config.hpp"

namespace Graphics
{
	std::vector<Vertex> SeaGenerator::generate()
	{
		std::vector<Vertex> vertices{};

		vertices.push_back({.pos = {-worldCameraFarPlane, 0, -worldCameraFarPlane},
			.texturePos = {}, .normalVector = {0, 1, 0}});
		vertices.push_back({.pos = {-worldCameraFarPlane, 0, worldCameraFarPlane},
			.texturePos = {}, .normalVector = {0, 1, 0}});
		vertices.push_back({.pos = {worldCameraFarPlane, 0, worldCameraFarPlane}, .texturePos = {},
			.normalVector = {0, 1, 0}});

		vertices.push_back({.pos = {-worldCameraFarPlane, 0, -worldCameraFarPlane},
			.texturePos = {}, .normalVector = {0, 1, 0}});
		vertices.push_back({.pos = {worldCameraFarPlane, 0, worldCameraFarPlane}, .texturePos = {},
			.normalVector = {0, 1, 0}});
		vertices.push_back({.pos = {worldCameraFarPlane, 0, -worldCameraFarPlane}, .texturePos = {},
			.normalVector = {0, 1, 0}});

		return vertices;
	}
}
