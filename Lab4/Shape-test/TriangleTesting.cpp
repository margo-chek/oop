#include "pch.h"
#include "../../Catch2/catch.hpp"
#include "../Shape/CTriangle.h"
#include "SecondaryFunctions.h"

using namespace std;



TEST_CASE("Triangle save own vertex")
{
	CTriangle triangle{ CPoint{1.1, 3.2}, CPoint{2, -5}, CPoint{-8, 4}, "fff000", "abc123" };

	REQUIRE(IsPointEqual(triangle.GetVertex1(), CPoint{ 1.1, 3.2 }));
	REQUIRE(IsPointEqual(triangle.GetVertex2(), CPoint{ 2.0, -5.0 }));
	REQUIRE(IsPointEqual(triangle.GetVertex3(), CPoint{ -8.0, 4.0 }));
}

TEST_CASE("Triangle can return own perimeter")
{
	CTriangle triangle{ CPoint{ 3, -3 }, CPoint{ 7, -3 }, CPoint{ 5, 5 }, "fff000", "abc123" };
	REQUIRE(RoundWithDecimal(triangle.GetPerimeter()) == 20.49);
}

TEST_CASE("Triagle can return own area")
{
	CTriangle triangle{ CPoint{ 3, -3 }, CPoint{ 7, -3 }, CPoint{ 5, 5 }, "fff000", "abc123" };
	REQUIRE(triangle.GetArea() == 16);
}

TEST_CASE("Triagle can return own outline color")
{
	CTriangle triangle{ CPoint{ 3, -3 }, CPoint{ 7, -3 }, CPoint{ 5, 5 }, "fff000", "abc123" };
	REQUIRE(triangle.GetOutlineColor() == static_cast<string>("fff000"));
}

TEST_CASE("Triagle can return own fill color")
{
	CTriangle triangle{ CPoint{ 3, -3 }, CPoint{ 7, -3 }, CPoint{ 5, 5 }, "fff000", "abc123" };
	REQUIRE(triangle.GetFillColor() == static_cast<string>("abc123"));
}
