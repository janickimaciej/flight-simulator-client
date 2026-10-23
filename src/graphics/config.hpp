#pragma once

#include <glm/glm.hpp>

namespace Graphics
{
	inline constexpr glm::vec2 characterSize{42, 82};
	inline constexpr float cameraNearPlane = 15;
	inline constexpr float cameraFarPlane = 40000;
	inline constexpr float waterTransparencyDepth = 50;
}
