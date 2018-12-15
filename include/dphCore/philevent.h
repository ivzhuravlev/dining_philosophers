#pragma once

namespace dph
{
	enum Event
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
	
	struct PhilosopherEvent
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
		
