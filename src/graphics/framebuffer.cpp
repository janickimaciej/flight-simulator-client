#include "graphics/framebuffer.hpp"

namespace Graphics
{
	Framebuffer::Framebuffer(const glm::ivec2& size) :
		m_size{size}
	{
		glGenFramebuffers(1, &m_FBO);
		bind();

		createColorBuffer();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorBuffer,
			0);

		createDepthBuffer();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthBuffer,
			0);

		unbind();
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteRenderbuffers(1, &m_depthBuffer);
		glDeleteTextures(1, &m_colorBuffer);
		glDeleteFramebuffers(1, &m_FBO);
	}

	void Framebuffer::bind()
	{
		bind({0, 0}, m_size);
	}

	void Framebuffer::bind(const glm::ivec2& viewportOffset, const glm::ivec2& viewportSize)
	{
		glGetIntegerv(GL_VIEWPORT, m_previousViewport.data());
		glViewport(viewportOffset.x, viewportOffset.y, viewportSize.x, viewportSize.y);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}

	void Framebuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(m_previousViewport[0], m_previousViewport[1], m_previousViewport[2],
			m_previousViewport[3]);
	}

	void Framebuffer::bindColorTexture() const
	{
		glBindTexture(GL_TEXTURE_2D, m_colorBuffer);
	}

	void Framebuffer::bindDepthTexture() const
	{
		glBindTexture(GL_TEXTURE_2D, m_depthBuffer);
	}

	void Framebuffer::setSize(const glm::ivec2& size)
	{
		if (size == m_size) return;
		m_size = size;
		resizeColorBuffer();
		resizeDepthBuffer();
	}

	void Framebuffer::createColorBuffer()
	{
		glGenTextures(1, &m_colorBuffer);
		resizeColorBuffer();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Framebuffer::createDepthBuffer()
	{
		glGenTextures(1, &m_depthBuffer);
		resizeDepthBuffer();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Framebuffer::resizeColorBuffer() const
	{
		glBindTexture(GL_TEXTURE_2D, m_colorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_size.x, m_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE,
			nullptr);
	}

	void Framebuffer::resizeDepthBuffer() const
	{
		glBindTexture(GL_TEXTURE_2D, m_depthBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_size.x, m_size.y, 0,
			GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
	}
}
