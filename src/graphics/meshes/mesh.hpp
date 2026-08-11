#pragma once

#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/meshes/vertex.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace Graphics
{
	class Mesh
	{
	public:
		Mesh(const std::string& path);
		Mesh(ProceduralMeshName name, bool dynamic = false);
		~Mesh();

		void update(const std::vector<Vertex>& vertices);
		void render() const;

	private:
		bool m_dynamic{};
		std::size_t m_vertexCount{};
		unsigned int m_VBO{};
		unsigned int m_VAO{};

		void createBuffers(const std::vector<Vertex>& vertices);
	};
}
