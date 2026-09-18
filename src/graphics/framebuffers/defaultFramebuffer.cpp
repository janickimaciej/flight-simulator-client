#include "graphics/framebuffers/defaultFramebuffer.hpp"

namespace Graphics
{
	DefaultFramebuffer::DefaultFramebuffer(const glm::ivec2& size) :
		Framebuffer{size}
	{
		m_fbo = 0;
	}
}
