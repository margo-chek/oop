#include "pch.h"
#include "CShapeMaker.h"
#include "Point.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"


using namespace std;

CShapeMaker::CShapeMaker(std::istream &input)
	: m_actionMap({
		{ "line", std::bind(&CShapeMaker::MakeLine, this, std::placeholders::_1) },
		{ "triangle", std::bind(&CShapeMaker::MakeTriangle, this, std::placeholders::_1) },
		{ "rectangle", std::bind(&CShapeMaker::MakeRectangle, this, std::placeholders::_1) },
		{ "circle", std::bind(&CShapeMaker::MakeCircle, this, std::placeholders::_1) }
		}),
	m_input(input)
{

}

std::shared_ptr<IShape> CShapeMaker::ExecuteCommand() const
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string figure;
	strm >> figure;

	auto it = m_actionMap.find(figure);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return nullptr;
}

std::shared_ptr<IShape> CShapeMaker::MakeLine(std::istream & args) const
{
	CPoint startPoint{ 0,0 };
	CPoint endPoint{0,0};
	string outlineColor, input1, input2;

	try
	{
		args >> input1;
		args >> input2;
		startPoint.SetCoordinates(stod(input1), stod(input2));
		input1.clear();
		input2.clear();

		args >> input1;
		args >> input2;
		endPoint.SetCoordinates(stod(input1), stod(input2));

		args >> outlineColor;
	}
	catch (const exception& e)
	{
		std::cout << e.what() << std::endl;
		return nullptr;
	}

	return make_shared<CLineSegment>(startPoint, endPoint, outlineColor);

}

std::shared_ptr<IShape> CShapeMaker::MakeTriangle(std::istream & args) const
{
	string input1, input2, outlineColor, fillColor;
	CPoint vertex1{ 0,0 };
	CPoint vertex2{ 0,0 };
	CPoint vertex3{ 0,0 };

	try
	{
		args >> input1;
		args >> input2;
		vertex1.SetCoordinates(stod(input1), stod(input2));
		input1.clear();
		input2.clear();

		args >> input1;
		args >> input2;
		vertex2.SetCoordinates(stod(input1), stod(input2));
		input1.clear();
		input2.clear();

		args >> input1;
		args >> input2;
		vertex3.SetCoordinates(stod(input1), stod(input2));
		input1.clear();
		input2.clear();

		args >> outlineColor;

		args >> fillColor;
	}
	catch (const exception& e)
	{
		std::cout << e.what() << std::endl;
		return nullptr;
	}
	return make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

std::shared_ptr<IShape> CShapeMaker::MakeRectangle(std::istream & args) const
{
	string input1, input2, outlineColor, fillColor;
	CPoint leftTop{ 0,0 };
	CPoint rightBottom{ 0,0 };
	double width, height;

	try
	{
		args >> input1;
		args >> input2;
		leftTop.SetCoordinates(stod(input1), stod(input2));
		input1.clear();
		input2.clear();

		args >> input1;
		args >> input2;
		rightBottom.SetCoordinates(stod(input1), stod(input2));
		input1.clear();
		input2.clear();

		args >> outlineColor;
		args >> fillColor;

	}
	catch (const exception& e)
	{
		std::cout << e.what() << std::endl;
		return nullptr;
	}

	return make_shared<CRectangle>(leftTop, rightBottom, outlineColor, fillColor);
}

std::shared_ptr<IShape> CShapeMaker::MakeCircle(std::istream & args) const
{
	CPoint center{ 0,0 };
	double radius;
	string input1, input2, outlineColor, fillColor;

	try
	{
		args >> input1;
		args >> input2;
		center.SetCoordinates(stod(input1), stod(input2));
		input1.clear();
		input2.clear();

		args >> input1;
		radius = stod(input1);
		input1.clear();

		args >> outlineColor;
		args >> fillColor;
	}
	catch (const exception& e)
	{
		std::cout << e.what() << std::endl;
		return nullptr;
	}

	return make_shared<CCircle>(center, radius, outlineColor, fillColor);
}

