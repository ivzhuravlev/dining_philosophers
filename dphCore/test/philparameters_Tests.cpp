#include<catch2/catch.hpp>
#include "philparameters.h"

TEST_CASE("Philparameters default constraction", "[core]")
{
	const int ordNum = 5;
	dph::PhilParameters params(ordNum);
	REQUIRE(params.ordinalNumber == ordNum);
}
