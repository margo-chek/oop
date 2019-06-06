#include "pch.h"
#include "CCircle.h"
#include <cmath>

using namespace std;

constexpr double PI = 3.141592653589793238463;


CCircle::CCircle(CPoint const& center, double radious, std::string const& outlineColor, std::string const& fillColor):
	m_center(center),
	m_radius(radious),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * PI * m_radius;
}

std::string CCircle::ToString() const
{
	return static_cast<string>("Shape: circle ") + static_cast<string>("Area: ") + to_string(GetArea()) +
		static_cast<string>(" Perimetr: ") + to_string(GetPerimeter()) +
		static_cast<string>(" Outline color: ") + GetOutlineColor() +
		static_cast<string>(" Fill color: ") + GetFillColor() + "\n";
}

std::string CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

