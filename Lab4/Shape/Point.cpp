#include "pch.h"
#include "Point.h"

using namespace std;

CPoint::CPoint(const double x, const double y) :
	m_x (x),
	m_y (y)
{
}

std::pair<double, double> CPoint::GetCoordinates() const
{
	pair<double, double > coordinates{m_x, m_y};

	return coordinates;
}

void CPoint::SetCoordinates(const double x, const double y)
{
	m_x = x;
	m_y = y;
}

double CPoint::GetCoordinateX() const
{
	return m_x;
}

double CPoint::GetCoordinateY() const
{
	return m_y;
}

