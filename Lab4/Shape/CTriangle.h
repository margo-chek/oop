#pragma once
#include "ISolidShape.h"
#include "Point.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, 
		std::string const& outlineColor, std::string const& fillColor);

	//возвращает площадь
	double GetArea() const override;

	//возвращает периметр
	double GetPerimeter() const override;

	//возвращает информацию о фигуре
	std::string ToString() const override;

	//возвращает цвет обводки фигуры
	std::string GetOutlineColor() const override;

	//возвращает цвет фигуры
	std::string GetFillColor() const override;


	//возвращает координаты первой вершины
	CPoint GetVertex1() const;

	//возвращает координаты второй вершины
	CPoint GetVertex2() const;

	//возвращает координаты третий вершины
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	std::string m_outlineColor;
	std::string m_fillColor;
};

