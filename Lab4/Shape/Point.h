#pragma once
#include <utility>

class CPoint
{
public:
	CPoint(const double x, const double y);

	//возвращает координаты точки
	std::pair<double, double> GetCoordinates() const;

	//назначает новые координаты точки
	void SetCoordinates(const double x, const double y);

	//возвращает координату x
	double GetCoordinateX() const;

	//возвращает координату y
	double GetCoordinateY() const;

private:
	double m_x = 0;
	double m_y = 0;

};

