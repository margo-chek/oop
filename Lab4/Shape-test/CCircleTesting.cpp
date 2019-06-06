#include "pch.h"
#include "../../Catch2/catch.hpp"
#include "../Shape/CCircle.h"
#include "SecondaryFunctions.h"

using namespace std;

TEST_CASE("Circle can return own center point")
{
	CCircle circle(CPoint{ 2, 3 }, 3, "fff000", "abc123");
	REQUIRE(IsPointEqual(circle.GetCenter(), CPoint{ 2, 3 }));
}

TEST_CASE("Circle can return own radius")
{
	CCircle circle(CPoint{ 2, 3 }, 3, "fff000", "abc123");
	REQUIRE(circle.GetRadius() == 3);
}

TEST_CASE("Circle can return own fill color")
{
	CCircle circle(CPoint{ 2, 3 }, 3, "fff000", "abc123");
	REQUIRE(circle.GetFillColor() == static_cast<string>("abc123"));
}

TEST_CASE("Circle can return own outline color")
{
	CCircle circle(CPoint{ 2, 3 }, 3, "fff000", "abc123");
	REQUIRE(circle.GetOutlineColor() == static_cast<string>("fff000"));
}

TEST_CASE("Circle can return own area")
{
	CCircle circle(CPoint{ 2, 3 }, 3, "fff000", "abc123");
	REQUIRE(RoundWithDecimal(circle.GetArea()) == 28.27);
}

TEST_CASE("Circle can return own perimetr")
{
	CCircle circle(CPoint{ 2, 3 }, 3, "fff000", "abc123");
	REQUIRE(RoundWithDecimal(circle.GetPerimeter()) == 18.85);
}