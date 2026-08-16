#include "graphics/meshes/quadGenerator.hpp"

#include <glm/glm.hpp>

#include <array>

namespace Graphics
{
	std::vector<Vertex> QuadGenerator::generate(const glm::vec2& size, bool inverted)
	{
		glm::vec2 sizeHalf = size / 2.0f;
		glm::vec3 normalVector{0, 0, 1};

		std::vector<Vertex> vertices{};

		std::array<Vertex, 3> triangle1{};
		triangle1[0].pos = glm::vec3{-sizeHalf.x, -sizeHalf.y, 0};
		triangle1[0].texturePos = glm::vec2{0, inverted ? 1 : 0};
		triangle1[0].normalVector = normalVector;
		triangle1[1].pos = glm::vec3{sizeHalf.x, -sizeHalf.y, 0};
		triangle1[1].texturePos = glm::vec2{1, inverted ? 1 : 0};
		triangle1[1].normalVector = normalVector;
		triangle1[2].pos = glm::vec3{-sizeHalf.x, sizeHalf.y, 0};
		triangle1[2].texturePos = glm::vec2{0, inverted ? 0 : 1};
		triangle1[2].normalVector = normalVector;

		vertices.push_back(triangle1[0]);
		vertices.push_back(triangle1[1]);
		vertices.push_back(triangle1[2]);

		std::array<Vertex, 3> triangle2{};
		triangle2[0].pos = glm::vec3{-sizeHalf.x, sizeHalf.y, 0};
		triangle2[0].texturePos = glm::vec2{0, inverted ? 0 : 1};
		triangle2[0].normalVector = normalVector;
		triangle2[1].pos = glm::vec3{sizeHalf.x, -sizeHalf.y, 0};
		triangle2[1].texturePos = glm::vec2{1, inverted ? 1 : 0};
		triangle2[1].normalVector = normalVector;
		triangle2[2].pos = glm::vec3{sizeHalf.x, sizeHalf.y, 0};
		triangle2[2].texturePos = glm::vec2{1, inverted ? 0 : 1};
		triangle2[2].normalVector = normalVector;

		vertices.push_back(triangle2[0]);
		vertices.push_back(triangle2[1]);
		vertices.push_back(triangle2[2]);

		return vertices;
	}
}
