#pragma once

#include <chrono>

namespace dph
{
	using namespace std::chrono_literals;

	struct PhilParameters
	{
		PhilParameters(int ord, std::chrono::milliseconds eatDur = 1000ms, std::chrono::milliseconds thDur = 1200ms) :
			ordinalNumber(ord),
			eatDuration(eatDur),
			thinkDuration(thDur)
			{}
		
		int ordinalNumber;
		std::chrono::milliseconds eatDuration;
		std::chrono::milliseconds thinkDuration;
	};
}