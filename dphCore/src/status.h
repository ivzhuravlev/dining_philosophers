#pragma once

namespace dph
{
	class enum PhilosopherEvent
	{
		Eating = 0,
		Thinking,
		Waiting,
		LeftForkTaken,
		RightForkTaken,
		LeftForkReleased,
		RightForkReleased
	}
	
	class enum PhilosopherStatus
	{
		Eat = 0,
		Think,
		Wait
	}
	
	class enum ForkStatus
	{
		Available = 0,
		Occupied
	}
}