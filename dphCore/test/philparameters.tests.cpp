#include <catch2/catch.hpp>
#include "philparameters.h"
#include <chrono>

TEST_CASE("Philparameters default constraction", "[core]")
{
	using namespace std::chrono_literals;
	const int ordNum = 5;
	dph::PhilParameters params(ordNum);
	CHECK(params.ordinalNumber == ordNum);
	CHECK(params.eatDuration == 300ms);
	CHECK(params.thinkDuration == 800ms);
}
