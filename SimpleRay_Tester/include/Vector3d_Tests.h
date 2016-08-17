#include <Catch\catch.hpp>
#include "Vector3d.h"
#include <limits>
#include <cmath>
#include "Comparator.h"

//Easier to type
typedef Vector3d<double> vec3;


//Test Constructors of the Vector3d class
TEST_CASE("Vector3d Initializers Tests", "[Vector3d]")
{
	Vector3d<int> a = Vector3d<int>();
	REQUIRE(((a.x == 0) && (a.y == 0) && (a.z == 0)));

	vec3 b = vec3(2.0, 4.5, 6.7);
	REQUIRE((floatEq(2.0, b.x) && floatEq(4.5, b.y) && floatEq(6.7, b.z)));
	
	vec3 c = vec3(2.0);
	REQUIRE((floatEq(2.0, c.x) && floatEq(2.0, c.y) && floatEq(2.0, c.z)));
}

//Test Dot Product of the Vector3d class
TEST_CASE("Vector3d Dot Products Tests", "[Vector3d]")
{
	vec3 a(2.0, 3.0, 4.0);
	vec3 b(3.0, -1.2, 2.3); 
	REQUIRE(floatEq(11.60, a.dot(b)));

	vec3 c(0.0, 0.0, 0.0);
	REQUIRE((floatEq(a.dot(c), 0.0) && floatEq(b.dot(c), 0.0) && floatEq(c.dot(a), 0.0)));

}


//Test Elementwise Product of the Vector3d class
TEST_CASE("Vector3d Elementwise Product Tests", "[Vector3d]")
{
	vec3 a(2.0, 3.0, 4.0);
	vec3 b(3.0, -1.2, 2.3);
	vec3 c(0.0, 0.0, 0.0);

	//TODO implement == operations
	REQUIRE(a*b == vec3(2.0*3.0, 3.0*(-1.2),4.0*2.3));
	REQUIRE(c == c);
}


//Test Addition of the Vector3d class
TEST_CASE("Vector3d Addition/Subtraction Tests", "[Vector3d]")
{
	vec3 a(2.0, 3.0, 4.0);
	vec3 b(3.0, -1.2, 2.3);
	vec3 c(0.0, 0.0, 0.0);

	//TODO implement == operations
	REQUIRE(a - b == vec3(2.0-3.0, 3.0+1.2, 4.0-2.3));
	REQUIRE(a + b == vec3(2.0 + 3.0, 3.0 - 1.2, 4.0 + 2.3));
	REQUIRE(c + c == vec3(0));
	REQUIRE(a + c == a);
}

//Test Mix Convolution of the Vector3d class
TEST_CASE("Vector3d Mix Tests", "[Vector3d]")
{
	vec3 a(2.0, 3.0, 4.0);
	vec3 b(3.0, -1.2, 2.3);

	vec3 mix1 = a.mix(b);
	vec3 mix2 = a.mix(b, .3);
	REQUIRE((floatEq(mix1.x, 2.50) && floatEq(mix1.y, 0.90) && floatEq(mix1.z, 3.15)));
	REQUIRE((floatEq(mix2.x, 2.70) && floatEq(mix2.y, 0.06) && floatEq(mix2.z, 2.81)));


}


//Test Normalize of the Vector3d class
TEST_CASE("Vector3d Normalize Tests", "[Vector3d]")
{
	vec3 a(2.0, 3.0, 4.0);
	vec3 b(1.0, -1.2, 2.3);
	vec3 c(0.0, 0.0, 0.0);
	REQUIRE((floatEq(a.normalize().x, .3713906764, 0.00000001) 
		&& floatEq(a.normalize().y, .5570860145, 0.00000001)
		&& floatEq(a.normalize().z, .7427813527, 0.00000001)));

	REQUIRE((floatEq(b.normalize().x, .3596750006, 0.00000001)
		&& floatEq(b.normalize().y, -.4316100007, 0.00000001)
		&& floatEq(b.normalize().z, .8272525014, 0.00000001)));

	REQUIRE(c.normalize() == vec3(0.0));

}

//Test Lengths of the Vector3d class
TEST_CASE("Vector3d Length Tests", "[Vector3d]")
{
	vec3 a(1.0, 0.0, 0.0);
	vec3 b(4.0, 3.0, 0.0);
	vec3 c(0.0, 0.0, 0.0);

	REQUIRE(a.length() == 1.0);
	REQUIRE(b.length() == 5.0);
	REQUIRE(c.length() == 0.0);
}