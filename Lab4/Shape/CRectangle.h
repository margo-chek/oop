#pragma once
#include "ISolidShape.h"
#include "Point.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint const& leftTop, CPoint const& rightBottom, 
		std::string const& outlineColor, std::string const& fillColor);
	
	//возврашает площадь прямоугольника
	double GetArea() const override;
	
	//возвращает периметр прямоугольника
	double GetPerimeter() const override;

	//возращает описание прямоугольника
	std::string ToString() const override;

	//возвращает цвет линии прямоугольника
	std::string GetOutlineColor() const override;

	//возвращает цвет прямоугольника
	std::string GetFillColor() const override;

	//возращает левую верхнюю точку прямоугольника
	CPoint GetLeftTop() const;

	//возращает правую нижнюю точку прямоугольника
	CPoint GetRightBottom() const;

	//возвращает ширину прямоугольника
	double GetWidth() const;

	//возвращает высоту прямоугольника
	double GetHeight() const;

private:
	CPoint m_leftTopPoint;
	CPoint m_rightBottomPoint;
	double m_width;
	double m_height;
	std::string m_outlineColor;
	std::string m_fillColor;
};

