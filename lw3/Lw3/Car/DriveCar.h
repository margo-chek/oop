#pragma once
#include "pch.h"
#include "Car.h"

class CDriveCar
{
public:
	CDriveCar(CCar &car, std::istream & input, std::ostream & output);
	bool ExecuteCommand();

private:
	bool EngineOn(std::istream & args);
	bool EngineOff(std::istream & args);
	bool Info(std::istream & args) const;
	bool SetGear(std::istream & args);
	bool SetSpeed(std::istream & args);

private:
	typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;

	CCar &m_car;
	std::istream &m_input;
	std::ostream &m_output;

	const ActionMap m_actionMap;
};
