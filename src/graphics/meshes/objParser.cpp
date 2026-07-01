#include "graphics/meshes/objParser.hpp"

#include "graphics/meshes/vertex.hpp"

#include <glm/glm.hpp>

#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace Graphics
{
	std::vector<Vertex> ObjParser::parse(const std::string& path)
	{
		std::ifstream file{path};
		if (!file)
		{
			std::cerr << "File does not exist:\n" << path << '\n';
			assert(false);
			return std::vector<Vertex>{};
		}

		std::vector<Vertex> vertices{};

		std::vector<glm::vec3> poss{};
		std::vector<glm::vec2> texturePoss{};
		std::vector<glm::vec3> normalVectors{};

		std::string line{};
		while (std::getline(file, line))
		{
			if (line[0] == 'v' && line[1] == ' ')
			{
				poss.push_back(parsePos(line));
			}
			else if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
			{
				texturePoss.push_back(parseTexturePos(line));
			}
			else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
			{
				normalVectors.push_back(parseNormalVector(line));
			}
			else if (line[0] == 'f' && line[1] == ' ')
			{
				std::array<Vertex, 3> triangle =
					parseTriangle(line, poss, texturePoss, normalVectors);
				vertices.push_back(triangle[0]);
				vertices.push_back(triangle[1]);
				vertices.push_back(triangle[2]);
			}
		}

		return vertices;
	}

	glm::vec3 ObjParser::parsePos(const std::string_view line)
	{
		glm::vec3 pos{};

		int component = 0;
		std::string number = "";
		for (auto c = line.begin() + 2; c != line.end(); ++c)
		{
			if (*c == ' ')
			{
				pos[component] = std::stof(number);
				++component;
				number = "";
			}
			else
			{
				number.push_back(*c);
			}
		}
		pos[component] = std::stof(number);

		return pos;
	}

	glm::vec2 ObjParser::parseTexturePos(const std::string_view line)
	{
		glm::vec2 texturePos{};

		int component = 0;
		std::string number = "";
		for (auto c = line.begin() + 3; c != line.end(); ++c)
		{
			if (*c == ' ')
			{
				texturePos[component] = std::stof(number);
				++component;
				number = "";
			}
			else
			{
				number.push_back(*c);
			}
		}
		texturePos[component] = std::stof(number);

		return texturePos;
	}

	glm::vec3 ObjParser::parseNormalVector(const std::string_view line)
	{
		glm::vec3 normalVector{};

		int component = 0;
		std::string number = "";
		for (auto c = line.begin() + 3; c != line.end(); ++c)
		{
			if (*c == ' ')
			{
				normalVector[component] = std::stof(number);
				++component;
				number = "";
			}
			else
			{
				number.push_back(*c);
			}
		}
		normalVector[component] = std::stof(number);

		return normalVector;
	}

	std::array<Vertex, 3> ObjParser::parseTriangle(const std::string_view line,
		const std::vector<glm::vec3>& poss, const std::vector<glm::vec2>& texturePoss,
		const std::vector<glm::vec3>& normalVectors)
	{
		std::array<Vertex, 3> triangle;

		std::size_t vertexIndex = 0;
		std::string number = "";
		std::size_t posIndex = 0;
		std::size_t normalVectorIndex = 0;
		std::size_t texturePosIndex = 0;
		bool isFirstNumber = true;
		for (auto c = line.begin() + 2; c != line.end(); ++c)
		{
			if (*c == ' ')
			{
				normalVectorIndex = static_cast<std::size_t>(std::stoi(number));
				number = "";
				if (vertexIndex < 3)
				{
					triangle[vertexIndex].pos = poss[posIndex - 1];
					triangle[vertexIndex].texturePos =
						texturePoss[texturePosIndex - 1];
					triangle[vertexIndex].normalVector = normalVectors[normalVectorIndex - 1];
				}
				++vertexIndex;
			}
			else if (*c == '/')
			{
				if (isFirstNumber)
				{
					posIndex = static_cast<std::size_t>(std::stoi(number));
				}
				else
				{
					texturePosIndex = static_cast<std::size_t>(std::stoi(number));
				}
				number = "";
				isFirstNumber = !isFirstNumber;
			}
			else
			{
				number.push_back(*c);
			}
		}
		normalVectorIndex = static_cast<std::size_t>(std::stoi(number));
		if (vertexIndex < 3)
		{
			triangle[vertexIndex].pos = poss[posIndex - 1];
			triangle[vertexIndex].texturePos = texturePoss[texturePosIndex - 1];
			triangle[vertexIndex].normalVector = normalVectors[normalVectorIndex - 1];
		}

		return triangle;
	}
}
