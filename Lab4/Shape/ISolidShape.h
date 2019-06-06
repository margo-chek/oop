#pragma once
#include "IShape.h"
class ISolidShape :	public IShape
{
public:
	virtual std::string GetFillColor() const = 0;
};

