#pragma once

#include "graphics/framebuffers/framebuffer.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <array>
#include <optional>

namespace Graphics
{
	class CustomFramebuffer : public Framebuffer
	{
	public:
		CustomFramebuffer(const glm::ivec2& size, bool multisample = false);
		virtual ~CustomFramebuffer();
		CustomFramebuffer& colorTexture();
		CustomFramebuffer& depthTexture();

		void bindColorTexture(unsigned int unit = 0) const;
		void bindDepthTexture(unsigned int unit = 0) const;

	private:
		bool m_multisample{};
		std::optional<unsigned int> m_colorBuffer{};
		std::optional<unsigned int> m_depthBuffer{};

		virtual void resizeBuffers() const override;

		void createColorBuffer();
		void createDepthBuffer();

		void resizeColorBuffer() const;
		void resizeDepthBuffer() const;

		GLenum getTextureTarget() const;
	};
}
