#pragma once

#include <glad/glad.h>

#include <string>

namespace Graphics
{
	class Texture
	{
	public:
		enum class Wrapping
		{
			repeat,
			mirroredRepeat,
			clampToEdge,
			clampToBorder
		};

		Texture(const std::string& id);
		void use() const;
		~Texture();

		static std::string getId(const std::string& path, Wrapping wrappingS = Wrapping::repeat,
			Wrapping wrappingT = Wrapping::repeat);

	private:
		unsigned int m_id;

		void create(GLint wrappingS, GLint wrappingT);
		void load(const std::string& path) const;
	};
}
