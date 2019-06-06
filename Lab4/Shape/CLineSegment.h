#pragma once
#include "IShape.h"
#include "Point.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint & first, const CPoint & second, const std::string& color);

	//���������� �������
	double GetArea() const override;

	//���������� ��������
	double GetPerimeter() const override;

	//���������� ���������� � ������
	std::string ToString() const override;

	//���������� ���� ������� ������
	std::string GetOutlineColor() const override;

	//���������� ���������� ��������� �����
	CPoint GetStartPoint() const;

	//���������� ���������� �������� �����
	CPoint GetEndPoint() const;


private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	std::string m_color;
};

