#pragma once
#include <chrono>
#include "dphCore_global.h"

namespace dph
{
	using namespace std::chrono_literals;

	struct DPHCORE_EXPORT DinnerSettings
	{
		DinnerSettings(int philnum,
			std::chrono::milliseconds eatdur,
			std::chrono::milliseconds thinkdur) :
			philNum(philnum),
			eatDur(eatdur),
			thinkDur(thinkdur)
		{}

		DinnerSettings(int philnum, int eatdur, int thinkdur) :
			DinnerSettings(philnum, std::chrono::milliseconds(eatdur),
									std::chrono::milliseconds(thinkdur))
		{}

		DinnerSettings() :
			DinnerSettings(5, 300ms, 300ms)
		{}

		int philNum;
		std::chrono::milliseconds eatDur;
		std::chrono::milliseconds thinkDur;
	};

	DPHCORE_EXPORT inline bool operator==(const DinnerSettings& lhs, const DinnerSettings& rhs)
	{
		return lhs.philNum == rhs.philNum &&
			lhs.eatDur == rhs.eatDur &&
			lhs.thinkDur == rhs.thinkDur;
	}

	DPHCORE_EXPORT inline bool operator!=(const DinnerSettings& lhs, const DinnerSettings& rhs)
	{
		return !(lhs == rhs);
	}

}