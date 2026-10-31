#include "graphics/time.hpp"

#include <cmath>

namespace Graphics
{
	void Time::initialize()
	{
		update();
	}

	void Time::update()
	{
		std::chrono::time_point<std::chrono::system_clock> currTime =
			std::chrono::system_clock::now();
		m_deltaTime = currTime - m_time;
		m_time = currTime;
	}

	float Time::getDeltaTime()
	{
		return m_deltaTime.count();
	}

	int Time::getFPS()
	{
		return static_cast<int>(std::round(1.0f / m_deltaTime.count()));
	}

	std::chrono::time_point<std::chrono::system_clock> Time::m_time{};
	std::chrono::duration<float> Time::m_deltaTime{};
}
