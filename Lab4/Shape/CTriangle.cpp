#include "pch.h"
#include "CTriangle.h"
#include <cmath>
#include <string>

using namespace std;

CTriangle::CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, std::string const& outlineColor, std::string const& fillColor) :
	m_vertex1(vertex1),
	m_vertex2(vertex2),
	m_vertex3(vertex3),
	m_outlineColor(outlineColor),
	m_fillColor(fillColor)
{

}

double FindTriagleSideByCoordinates(CPoint const& p1, CPoint const& p2)
{
	return sqrt( pow((p2.GetCoordinateX() - p1.GetCoordinateX()), 2) + pow((p2.GetCoordinateY() - p1.GetCoordinateY()) ,2) );
}

double FindDeterminant2x2(double matrix[2][2])
{
	return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

double CTriangle::GetArea() const
{
	double matrix[2][2];
	matrix[0][0] = m_vertex1.GetCoordinateX() - m_vertex3.GetCoordinateX();
	matrix[0][1] = m_vertex1.GetCoordinateY() - m_vertex3.GetCoordinateY();
	matrix[1][0] = m_vertex2.GetCoordinateX() - m_vertex3.GetCoordinateX();
	matrix[1][1] = m_vertex2.GetCoordinateY() - m_vertex3.GetCoordinateY();

 	return fabs(FindDeterminant2x2(matrix)) * 0.5;
}

double CTriangle::GetPerimeter() const
{
	double side1 = FindTriagleSideByCoordinates(m_vertex1, m_vertex2);
	double side2 = FindTriagleSideByCoordinates(m_vertex2, m_vertex3);
	double side3 = FindTriagleSideByCoordinates(m_vertex1, m_vertex3);

	return side1 + side2 + side3;
}

std::string CTriangle::ToString() const
{
	return static_cast<string>("Shape: triangle") + static_cast<string>("Area: ") + to_string(GetArea()) +
		static_cast<string>(" Perimetr: ") + to_string(GetPerimeter()) + 
		static_cast<string>(" Outline color: ") + GetOutlineColor() + 
		static_cast<string>(" Fill color: ") + GetFillColor() + "\n";
}

std::string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
