#include "pch.h"
#include "../../Catch2/catch.hpp"
#include "../Shape/Point.h"

using namespace std;

TEST_CASE("Point save coordinates")
{
	pair<double, double> etalonCordinates{ 0, 0 };
	CPoint point{ 0, 0 };
	
	pair<double, double> anotherCordinates{ 10, 0.5 };

	auto cordinates = point.GetCoordinates();
	REQUIRE(cordinates == etalonCordinates);
	REQUIRE(cordinates != anotherCordinates);

}

TEST_CASE("Can change coordinates of the point")
{
	CPoint point{ 0, 0 };
	pair<double, double> etalonCordinates{ 10, 15.5 };
	point.SetCoordinates(10, 15.5);
	REQUIRE(point.GetCoordinateX() == etalonCordinates.first);
	REQUIRE(point.GetCoordinateY() == etalonCordinates.second);
}

