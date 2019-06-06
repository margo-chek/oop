#include "pch.h"
#include "../../Catch2/catch.hpp"
#include "../Shape/CLineSegment.h"
#include "SecondaryFunctions.h"

using namespace std;

TEST_CASE("Line can save own coordiants")
{
	CLineSegment line{ CPoint {10.5, 15.3}, CPoint {15.6, 2}, "ff0000" };

	CHECK(IsPointEqual(line.GetStartPoint(), CPoint{ 10.5, 15.3 }));
	CHECK(IsPointEqual(line.GetEndPoint(), CPoint{ 15.6, 2 }));
}

TEST_CASE("Line can save own color")
{
	CLineSegment line{ CPoint{ 10.5, 15.3 }, CPoint{ 15.6, 2 }, "ff0000" };
	string color{ "ff0000" };
	CHECK(line.GetOutlineColor() == color);
}

TEST_CASE("Line have 0 area")
{
	CLineSegment line{ CPoint{ 10.5, 15.3 }, CPoint{ 15.6, 2 }, "ff0000" };
	CHECK(line.GetArea() == 0);
}

TEST_CASE("Line have perimeter")
{
	CLineSegment line{ CPoint{ 10.5, 15.3 }, CPoint{ 15.6, 2 }, "ff0000" };

	CHECK(RoundWithDecimal(line.GetPerimeter()) == 14.24); //14.24429
}
