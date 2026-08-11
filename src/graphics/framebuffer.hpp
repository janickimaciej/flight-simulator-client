#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <array>

namespace Graphics
{
	class Framebuffer
	{
	public:
		Framebuffer(const glm::ivec2& size);
		~Framebuffer();
		void bind();
		void bind(const glm::ivec2& viewportOffset, const glm::ivec2& viewportSize);
		void unbind() const;
		void bindColorTexture() const;
		void bindDepthTexture() const;
		void setSize(const glm::ivec2& size);

	private:
		unsigned int m_FBO{};
		unsigned int m_colorBuffer{};
		unsigned int m_depthBuffer{};
		glm::ivec2 m_size{};
		std::array<int, 4> m_previousViewport{};

		void createColorBuffer();
		void createDepthBuffer();

		void resizeColorBuffer() const;
		void resizeDepthBuffer() const;
	};
}
