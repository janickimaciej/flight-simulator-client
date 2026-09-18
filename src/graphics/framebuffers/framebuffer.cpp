#include "graphics/framebuffers/framebuffer.hpp"

namespace Graphics
{
	Framebuffer::Framebuffer(const glm::ivec2& size) :
		m_size{size}
	{ }
		
	void Framebuffer::setSize(const glm::ivec2& size)
	{
		if (size == m_size) return;
		m_size = size;
		resizeBuffers();
	}

	void Framebuffer::bind() const
	{
		bind({0, 0}, m_size);
	}

	void Framebuffer::bind(const glm::ivec2& viewportOffset, const glm::ivec2& viewportSize) const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glViewport(viewportOffset.x, viewportOffset.y, viewportSize.x, viewportSize.y);
	}

	void Framebuffer::clear(GLbitfield mask, const glm::vec3& background) const
	{
		glClearColor(background.r, background.g, background.b, 1.0f);
		glClear(mask);
	}

	void Framebuffer::blit(GLbitfield mask, const Framebuffer& source,
		const Framebuffer& destination)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, source.m_fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, destination.m_fbo);

		glBlitFramebuffer(0, 0, source.m_size.x, source.m_size.y, 0, 0, destination.m_size.x,
			destination.m_size.y, mask, GL_NEAREST);
	}

	glm::ivec2 Framebuffer::getSize() const
	{
		return m_size;
	}

	void Framebuffer::resizeBuffers() const
	{ }
}
