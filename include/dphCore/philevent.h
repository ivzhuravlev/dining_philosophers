#pragma once
#include "dphCore_global.h"

namespace dph
{
	enum DPHCORE_EXPORT Event
		{
			Eating = 0,
			Thinking,
			Waiting,
			LeftForkTaken,
			RightForkTaken,
			LeftForkReleased,
			RightForkReleased,
			Finished
		};
	
	struct DPHCORE_EXPORT PhilosopherEvent
	{
		PhilosopherEvent() = default;

		PhilosopherEvent(int num, Event e):
		number(num),
		event(e)
		{}
		
		int number;
		Event event;
	};
}
		
