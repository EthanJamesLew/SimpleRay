#include <Catch\catch.hpp>
#include "Convolution.h"
#include "Comparator.h"

//Test mix of the Convolution functions
TEST_CASE("Convolution Mix Tests", "[Convolutions]")
{
	double a = 3.0;
	double b = -2.3;
	double mixa = .3;
	double mixb = 0.0;
	
	REQUIRE(floatEq(convolution::mix(a, b) , 0.35));
	REQUIRE(floatEq(convolution::mix(a, b, mixa), -0.71));
	REQUIRE(floatEq(convolution::mix(a, b, mixb), b));
}

