#pragma once

#include "pch.h"
#include <iostream>
#include "DriveCar.h"
#include "Car.h"

using namespace std;

string ConvertErrorToString(const Error &error)
{
	switch (error)
	{
	case Error::ENGINE_IS_OFF:
		return "Engine is off";
	case Error::ENGINE_CAN_NOT_BE_TURNED_OFF:
		return "Engine can not be turned off";
	case Error::NO_ZERO_SPEED:
		return "First you need to stop";
	case Error::SPEED_IS_NOT_CORRECT_FOR_GEAR:
		return "Speed is not correct for gear";
	case Error::ONLY_REDUCE_THE_SPEED:
		return "Speed can only be reduced";
	case Error::SPEED_IS_NOT_CORRECT_FOR_REVERSE_GEAR:
		return "the speed can be from 0 to 20";
	case Error::SPEED_IS_NOT_CORRECT_FOR_FIRST_GEAR:
		return "the speed can be from 0 to 30";
	case Error::SPEED_IS_NOT_CORRECT_FOR_SECOND_GEAR:
		return "the speed can be from 20 to 50";
	case Error::SPEED_IS_NOT_CORRECT_FOR_THIRD_GEAR:
		return "the speed can be from 30 to 60";
	case Error::SPEED_IS_NOT_CORRECT_FOR_FOURTH_GEAR:
		return "the speed can be from 40 to 90";
	case Error::SPEED_IS_NOT_CORRECT_FOR_FIFTH_GEAR:
		return "the speed can be from 50 to 150";
	}
	return "not error";
}

CDriveCar::CDriveCar(CCar &car, istream & input, ostream & output)
	: m_car(car),
	m_input(input),
	m_output(output),
	m_actionMap({
		{ "EngineOn", bind(&CDriveCar::EngineOn, this, placeholders::_1) },
		{ "EngineOff", bind(&CDriveCar::EngineOff, this, placeholders::_1) },
		{ "Info", bind(&CDriveCar::Info, this, placeholders::_1) },
		{ "SetGear", bind(&CDriveCar::SetGear, this, placeholders::_1) },
		{ "SetSpeed", bind(&CDriveCar::SetSpeed, this, placeholders::_1) }
		})
{
}

bool CDriveCar::ExecuteCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CDriveCar::EngineOn(istream &)
{
	m_car.TurnOnEngine();
	m_output << "Engine is turned on" << endl;
	return true;
}

bool CDriveCar::EngineOff(istream &)
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine is turned off" << endl;
	}
	else
	{
		m_output << ConvertErrorToString(m_car.GetError()) << endl;
	}
	return true;
}

string ConvertDirectionToString(const Direction &direction)
{
	if (direction == Direction::Backward)
		return "backward";
	else if (direction == Direction::Stop)
		return "stop";
	else
		return "forward";
}

bool CDriveCar::Info(istream &) const
{
	string infoEngine = (m_car.IsEngineTurnOn()) ? ("Engine is turned on\n") : ("Engine is turned off\n");
	string infoSpeed = "Speed " + to_string(m_car.GetSpeed()) + "\n";
	string infoDirection = "Direction " + ConvertDirectionToString(m_car.GetDirection()) + "\n";
	string infoGear = "Gear " + to_string(m_car.GetGear());

	m_output << (infoEngine + infoSpeed + infoDirection + infoGear) << "\n";

	return true;
}

bool isAvailable(const string &arg, int &gear)
{
	try
	{
		gear = stoi(arg);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}

	return true;
}

bool CDriveCar::SetGear(istream &args)
{
	int gear;
	string input;
	args >> input;
	
	if (isAvailable(input, gear))
	{
		if ((gear < -1) || (gear > 5))
		{
			m_output << "Use a gear between -1 and 5" << endl;
		}
		else if (m_car.SetGear(gear))
		{
			m_output << "Selected gear " << gear << endl;
		}
		else
		{
			m_output << "Gear did not change" << endl;
			m_output << ConvertErrorToString(m_car.GetError()) << endl;
		}
	}
	else
	{
		m_output << "Invalid gear" << endl;
	}

	return true;
}

bool CDriveCar::SetSpeed(istream &args)
{
	int speed;
	string input;
	args >> input;

	if (isAvailable(input, speed))
	{
		if (speed < 0)
		{
			m_output << "Speed can not be negative" << endl;
		}
		else if (m_car.SetSpeed(speed))
		{
			m_output << "Selected speed " << speed << endl;
		}
		else
		{
			m_output << "Speed did not change" << endl;
			m_output << ConvertErrorToString(m_car.GetError()) << endl;
		}
	}
	else
	{
		m_output << "Invalid speed" << endl;
	}

	return true;
}
