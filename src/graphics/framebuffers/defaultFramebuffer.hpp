#pragma once

#include "graphics/framebuffers/framebuffer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Graphics
{
	class DefaultFramebuffer : public Framebuffer
	{
	public:
		DefaultFramebuffer(const glm::ivec2& size);
		virtual ~DefaultFramebuffer() = default;
	};
}
