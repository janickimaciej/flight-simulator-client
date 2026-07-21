#include "graphics/texture.hpp"

#include <stb_image.h>

#include <iostream>

namespace Graphics
{
	namespace
	{
		char getWrappingId(Texture::Wrapping wrapping)
		{
			switch (wrapping)
			{
				case Texture::Wrapping::repeat:
					return 'R';

				case Texture::Wrapping::mirroredRepeat:
					return 'M';

				case Texture::Wrapping::clampToEdge:
					return 'E';

				case Texture::Wrapping::clampToBorder:
					return 'B';
			}
			return {};
		}

		GLint parseWrappingId(char id)
		{
			switch (id)
			{
				case 'R':
					return GL_REPEAT;

				case 'M':
					return GL_MIRRORED_REPEAT;

				case 'E':
					return GL_CLAMP_TO_EDGE;

				case 'B':
					return GL_CLAMP_TO_BORDER;
			}
			return {};
		}
	}

	Texture::Texture(const std::string& id)
	{
		GLint wrappingS = parseWrappingId(id[0]);
		GLint wrappingT = parseWrappingId(id[1]);
		std::string path = id.substr(2);

		create(wrappingS, wrappingT);
		load(path);
	}

	void Texture::use() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_id);
	}

	std::string Texture::getId(const std::string& path, Wrapping wrappingS, Wrapping wrappingT)
	{
		char wrappingSId = getWrappingId(wrappingS);
		char wrappingTId = getWrappingId(wrappingT);

		return std::string{wrappingSId} + wrappingTId + path;
	}

	void Texture::create(GLint wrappingS, GLint wrappingT)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Texture::load(const std::string& path) const
	{
		int width{};
		int height{};
		int nrOfChannels{};
		unsigned char* textureData = stbi_load(path.c_str(), &width, &height, &nrOfChannels,
			STBI_rgb_alpha);
		if (textureData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
				textureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cerr << "Error loading texture: \n" << path << '\n';
		}
		stbi_image_free(textureData);
	}
}
