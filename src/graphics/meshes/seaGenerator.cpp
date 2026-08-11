#include "graphics/meshes/seaGenerator.hpp"

namespace Graphics
{
	std::vector<Vertex> SeaGenerator::generate()
	{
		std::vector<Vertex> vertices{};

		vertices.push_back({.pos = {-50000, 0, -50000}, .texturePos = {}, .normalVector = {0, 1, 0}});
		vertices.push_back({.pos = {-50000, 0, 50000}, .texturePos = {}, .normalVector = {0, 1, 0}});
		vertices.push_back({.pos = {50000, 0, 50000}, .texturePos = {}, .normalVector = {0, 1, 0}});

		vertices.push_back({.pos = {-50000, 0, -50000}, .texturePos = {}, .normalVector = {0, 1, 0}});
		vertices.push_back({.pos = {50000, 0, 50000}, .texturePos = {}, .normalVector = {0, 1, 0}});
		vertices.push_back({.pos = {50000, 0, -50000}, .texturePos = {}, .normalVector = {0, 1, 0}});

		return vertices;
	}
}
