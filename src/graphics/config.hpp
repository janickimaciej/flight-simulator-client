#pragma once

#include <glm/glm.hpp>

namespace Graphics
{
	inline constexpr glm::vec2 characterSize{42, 82};
	inline constexpr float worldCameraNearPlane = 4;
	inline constexpr float worldCameraFarPlane = 20000;
	inline constexpr float worldCameraFOVYDeg = 60;
}
