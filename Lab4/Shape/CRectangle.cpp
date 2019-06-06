#include "pch.h"
#include "CRectangle.h"
#include <cmath>
#include <string>

using namespace std;

CRectangle::CRectangle(CPoint const& leftTop, CPoint const& rightBottom,
	std::string const& outlineColor, std::string const& fillColor) :
	m_leftTopPoint(leftTop),
	m_rightBottomPoint(rightBottom),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{
	m_width = abs(m_rightBottomPoint.GetCoordinateX() - m_leftTopPoint.GetCoordinateX());
	m_height = abs(m_rightBottomPoint.GetCoordinateY() - m_leftTopPoint.GetCoordinateY());
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return m_width * 2 + m_height * 2;
}

std::string CRectangle::ToString() const
{
	return "Shape: rectangle "s + 
		"Area: "s + to_string(GetArea()) +
		" Perimetr: "s + to_string(GetPerimeter()) +
		" Outline color: "s + GetOutlineColor() +
		" Fill color: "s + GetFillColor() + 
		" Left Top point: ("s + to_string(GetLeftTop().GetCoordinateX()) + "  " + to_string(GetLeftTop().GetCoordinateY()) + ") " +
		" Right Bottom point: ("s + to_string(GetRightBottom().GetCoordinateX()) + "  " + to_string(GetRightBottom().GetCoordinateY()) + ") " +
		" Width: ("s + to_string(GetWidth()) + "  " +
		" Height: "s + to_string(GetHeight()) + 
		"\n"s;
}

std::string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottomPoint;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
