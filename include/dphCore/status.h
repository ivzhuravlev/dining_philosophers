#pragma once

namespace dph
{	
	enum class PhilosopherStatus
	{
		Eat = 0,
		Think,
		Wait,
		Finish
	};
	
	enum class ForkStatus
	{
		Available = 0,
		Occupied
	};
}
