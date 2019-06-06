#include "pch.h"
#include "SecondaryFunctions.h"

bool IsPointEqual(CPoint const& p1, CPoint const& p2)
{
	return ((p1.GetCoordinateX() == p2.GetCoordinateX()) && (p1.GetCoordinateY() == p2.GetCoordinateY())) ? true : false;
}

double RoundWithDecimal(double const & number)
{
	return round(number * 100) / 100;
}
