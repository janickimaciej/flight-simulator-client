#include "graphics/framebuffers/customFramebuffer.hpp"

namespace Graphics
{
	CustomFramebuffer::CustomFramebuffer(const glm::ivec2& size, bool multisample) :
		Framebuffer{size},
		m_multisample{multisample}
	{
		glGenFramebuffers(1, &m_fbo);
	}

	CustomFramebuffer::~CustomFramebuffer()
	{
		if (m_depthBuffer.has_value()) glDeleteTextures(1, &*m_depthBuffer);
		if (m_colorBuffer.has_value()) glDeleteTextures(1, &*m_colorBuffer);
		glDeleteFramebuffers(1, &m_fbo);
	}

	CustomFramebuffer& CustomFramebuffer::colorTexture()
	{
		bind();

		createColorBuffer();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, getTextureTarget(),
			*m_colorBuffer, 0);

		return *this;
	}

	CustomFramebuffer& CustomFramebuffer::depthTexture()
	{
		bind();
		createDepthBuffer();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, getTextureTarget(),
			*m_depthBuffer, 0);

		return *this;
	}

	void CustomFramebuffer::bindColorTexture() const
	{
		if (!m_colorBuffer.has_value()) return;
		glBindTexture(GL_TEXTURE_2D, *m_colorBuffer);
	}

	void CustomFramebuffer::bindDepthTexture() const
	{
		if (!m_depthBuffer.has_value()) return;
		glBindTexture(GL_TEXTURE_2D, *m_depthBuffer);
	}

	void CustomFramebuffer::resizeBuffers() const
	{
		if (m_colorBuffer.has_value()) resizeColorBuffer();
		if (m_depthBuffer.has_value()) resizeDepthBuffer();
	}

	void CustomFramebuffer::createColorBuffer()
	{
		unsigned int colorBuffer{};
		glGenTextures(1, &colorBuffer);
		m_colorBuffer = colorBuffer;
		resizeColorBuffer();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void CustomFramebuffer::createDepthBuffer()
	{
		unsigned int depthBuffer{};
		glGenTextures(1, &depthBuffer);
		m_depthBuffer = depthBuffer;
		resizeDepthBuffer();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void CustomFramebuffer::resizeColorBuffer() const
	{
		GLenum textureTarget = getTextureTarget();
		glBindTexture(textureTarget, *m_colorBuffer);
		glm::ivec2 size = getSize();
		if (m_multisample)
		{
			glTexImage2DMultisample(textureTarget, 4, GL_RGB, size.x, size.y,
				GL_TRUE);
		}
		else
		{
			glTexImage2D(textureTarget, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE,
				nullptr);
		}
	}

	void CustomFramebuffer::resizeDepthBuffer() const
	{
		GLenum textureTarget = getTextureTarget();
		glBindTexture(textureTarget, *m_depthBuffer);
		glm::ivec2 size = getSize();
		if (m_multisample)
		{
			glTexImage2DMultisample(textureTarget, 4, GL_DEPTH_COMPONENT, size.x, size.y,
				GL_TRUE);
		}
		else
		{
			glTexImage2D(textureTarget, 0, GL_DEPTH_COMPONENT, size.x, size.y, 0,
				GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		}
	}

	GLenum CustomFramebuffer::getTextureTarget() const
	{
		return m_multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}
}
