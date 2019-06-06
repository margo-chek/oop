#include "pch.h"
#include "CLineSegment.h"
#include <cmath>
#include <string>
using namespace std;

CLineSegment::CLineSegment(const CPoint & first, const CPoint & second, const std::string& color) :
	m_startPoint(first),
	m_endPoint(second),
	m_color(color)
{

}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_endPoint.GetCoordinateX() - m_startPoint.GetCoordinateX(), 2) + pow(m_endPoint.GetCoordinateY() - m_startPoint.GetCoordinateY(), 2));
}

std::string CLineSegment::ToString() const
{
	return static_cast<string>("Shape: line ") + static_cast<string>("Area: ") + to_string(GetArea()) +
		static_cast<string>(" Perimetr: ") + to_string(GetPerimeter()) + 
		static_cast<string>(" Outline color: ") + GetOutlineColor() + "\n";
}

std::string CLineSegment::GetOutlineColor() const
{
	return m_color;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

