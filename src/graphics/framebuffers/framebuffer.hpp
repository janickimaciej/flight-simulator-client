#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Graphics
{
	class Framebuffer
	{
	public:
		Framebuffer(const glm::ivec2& size);
		virtual ~Framebuffer() = default;
		
		void setSize(const glm::ivec2& size);
		void bind() const;
		void bind(const glm::ivec2& viewportOffset, const glm::ivec2& viewportSize) const;
		void clear(GLbitfield mask, const glm::vec3& background = {}) const;

		static void blit(GLbitfield mask, const Framebuffer& source,
			const Framebuffer& destination);

	protected:
		unsigned int m_fbo{};

		glm::ivec2 getSize() const;

	private:
		glm::ivec2 m_size{};

		virtual void resizeBuffers() const;
	};
}
