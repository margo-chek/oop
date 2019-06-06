#include "pch.h"
#include "../../Catch2/catch.hpp"
#include "../Shape/CRectangle.h"
#include "SecondaryFunctions.h"

using namespace std;

TEST_CASE("Rectange can return own width")
{
	CRectangle rectangle(CPoint{ 1, 5 }, CPoint{ 7, 1}, "fff000", "abc123");
	REQUIRE(rectangle.GetWidth() == 6);
}

TEST_CASE("Rectange can return own height")
{
	CRectangle rectangle(CPoint{ 1, 5 }, CPoint{ 7, 1 }, "fff000", "abc123");
	REQUIRE(rectangle.GetHeight() == 4);
}

TEST_CASE("Rectange can return own fill color")
{
	CRectangle rectangle(CPoint{ 1, 5 }, CPoint{ 7, 1 }, "fff000", "abc123");
	REQUIRE(rectangle.GetFillColor() == static_cast<string>("abc123"));
}

TEST_CASE("Rectange can return own outline color")
{
	CRectangle rectangle(CPoint{ 1, 5 }, CPoint{ 7, 1 }, "fff000", "abc123");
	REQUIRE(rectangle.GetOutlineColor() == static_cast<string>("fff000"));
}

TEST_CASE("Rectange can return own left top point")
{
	CRectangle rectangle(CPoint{ 1, 5 }, CPoint{ 7, 1 }, "fff000", "abc123");
	REQUIRE(IsPointEqual(rectangle.GetLeftTop(), CPoint{ 1, 5 }));
}

TEST_CASE("Rectange can return own right bottom point")
{
	CRectangle rectangle(CPoint{ 1, 5 }, CPoint{ 7, 1 }, "fff000", "abc123");
	REQUIRE(IsPointEqual(rectangle.GetRightBottom(), CPoint{ 7, 1 }));
}

TEST_CASE("Rectange can return own perimeter")
{
	CRectangle rectangle(CPoint{ 1, 5 }, CPoint{ 7, 1 }, "fff000", "abc123");
	REQUIRE(rectangle.GetPerimeter() == 20);
}

TEST_CASE("Rectange can return own area")
{
	CRectangle rectangle(CPoint{ 1, 5 }, CPoint{ 7, 1 }, "fff000", "abc123");
	REQUIRE(rectangle.GetArea() == 24);
}
