#pragma once
#include "pch.h"
#include "IShape.h"

class CShapeMaker
{
public:
	CShapeMaker(std::istream &input);
	std::shared_ptr<IShape> ExecuteCommand() const;

private:
	std::shared_ptr<IShape> MakeLine(std::istream &args) const;
	std::shared_ptr<IShape> MakeTriangle(std::istream &args) const;
	std::shared_ptr<IShape> MakeRectangle(std::istream &args) const;
	std::shared_ptr<IShape> MakeCircle(std::istream &args) const;

private:
	typedef std::map<std::string, std::function<std::shared_ptr<IShape>(std::istream & args)>> ActionMap;
	std::istream &m_input;
	const ActionMap m_actionMap;
};

