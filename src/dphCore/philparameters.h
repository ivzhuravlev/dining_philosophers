#pragma once

#include <chrono>

namespace dph
{
	struct PhilParameters
	{
		std::chrono::milliseconds eatDuration;
		std::chrono::milliseconds thinkDuration;
	}
}