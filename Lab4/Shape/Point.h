#pragma once
#include <utility>

class CPoint
{
public:
	CPoint(const double x, const double y);

	//���������� ���������� �����
	std::pair<double, double> GetCoordinates() const;

	//��������� ����� ���������� �����
	void SetCoordinates(const double x, const double y);

	//���������� ���������� x
	double GetCoordinateX() const;

	//���������� ���������� y
	double GetCoordinateY() const;

private:
	double m_x = 0;
	double m_y = 0;

};

