#pragma once
#include "IShape.h"
#include "Point.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint & first, const CPoint & second, const std::string& color);

	//возвращает площадь
	double GetArea() const override;

	//возвращает периметр
	double GetPerimeter() const override;

	//возвращает информацию о фигуре
	std::string ToString() const override;

	//возвращает цвет обводки фигуры
	std::string GetOutlineColor() const override;

	//возвращает координаты начальной точки
	CPoint GetStartPoint() const;

	//возвращает координаты конечной точки
	CPoint GetEndPoint() const;


private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	std::string m_color;
};

