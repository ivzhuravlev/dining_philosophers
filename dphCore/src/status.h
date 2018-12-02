#pragma once

namespace dph
{
	enum class PhilosopherEvent
	{
		Eating = 0,
		Thinking,
		Waiting,
		LeftForkTaken,
		RightForkTaken,
		LeftForkReleased,
		RightForkReleased
	};
	
	enum class PhilosopherStatus
	{
		Eat = 0,
		Think,
		Wait
	};
	
	enum class ForkStatus
	{
		Available = 0,
		Occupied
	};
}