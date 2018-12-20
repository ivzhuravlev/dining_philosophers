#pragma once
#include <chrono>

namespace dph
{
	using namespace std::chrono_literals;

	struct DinnerSettings
	{
		DinnerSettings(int philnum,
			std::chrono::milliseconds eatdur,
			std::chrono::milliseconds thinkdur) :
			philNum(philnum),
			eatDur(eatdur),
			thinkDur(thinkdur)
		{}

		DinnerSettings(int philnum, int eatdur, int thinkdur) :
			DinnerSettings(philNum, std::chrono::milliseconds(eatdur),
									std::chrono::milliseconds(thinkdur))
		{}

		DinnerSettings() :
			DinnerSettings(5, 300ms, 300ms)
		{}

		int philNum;
		std::chrono::milliseconds eatDur;
		std::chrono::milliseconds thinkDur;
	};

	inline bool operator==(const DinnerSettings& lhs, const DinnerSettings& rhs)
	{
		return lhs.philNum == rhs.philNum &&
			lhs.eatDur == rhs.eatDur &&
			lhs.thinkDur == rhs.thinkDur;
	}

	inline bool operator!=(const DinnerSettings& lhs, const DinnerSettings& rhs)
	{
		return !(lhs == rhs);
	}

}