#pragma once
#include "ISolidShape.h"
#include "Point.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, 
		std::string const& outlineColor, std::string const& fillColor);

	//���������� �������
	double GetArea() const override;

	//���������� ��������
	double GetPerimeter() const override;

	//���������� ���������� � ������
	std::string ToString() const override;

	//���������� ���� ������� ������
	std::string GetOutlineColor() const override;

	//���������� ���� ������
	std::string GetFillColor() const override;


	//���������� ���������� ������ �������
	CPoint GetVertex1() const;

	//���������� ���������� ������ �������
	CPoint GetVertex2() const;

	//���������� ���������� ������ �������
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	std::string m_outlineColor;
	std::string m_fillColor;
};

