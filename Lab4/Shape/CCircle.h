#pragma once
#include "ISolidShape.h"
#include "Point.h"

class CCircle :	public ISolidShape
{
public:
	CCircle(CPoint const& center, double radious, std::string const& outlineColor, std::string const& fillColor);

	//возвращает площадь окружности
	double GetArea() const override;

	//возвращает периметр окружности
	double GetPerimeter() const override;

	//возвращает информацию об окружности
	std::string ToString() const override;

	//возвращает цвет обводки окружности
	std::string GetOutlineColor() const override;

	//возвращает цвет окружности
	std::string GetFillColor() const override;

	//возвращет координаты центра окружности
	CPoint GetCenter() const;

	//возвращает радиус окружности
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
	std::string m_outlineColor;
	std::string m_fillColor;
};

