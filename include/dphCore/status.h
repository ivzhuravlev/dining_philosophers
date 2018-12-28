#pragma once
#include "dphCore_global.h"

namespace dph
{	
	enum class DPHCORE_EXPORT PhilosopherStatus
	{
		Eat = 0,
		Think,
		Wait,
		Finish
	};
	
	enum class DPHCORE_EXPORT ForkStatus
	{
		Available = 0,
		Occupied
	};
}
