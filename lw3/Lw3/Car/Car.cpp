#include "pch.h"
#include "Car.h"

bool IsCorrectSpeedForGear(int gear, unsigned int speed)
{
	if ((gear == -1 && speed >= 0 && speed <= 20) ||
		(gear == 1 && speed >= 0 && speed <= 30) ||
		(gear == 2 && speed >= 20 && speed <= 50) ||
		(gear == 3 && speed >= 30 && speed <= 60) ||
		(gear == 4 && speed >= 40 && speed <= 90) ||
		(gear == 5 && speed >= 50 && speed <= 150))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCar::IsEngineTurnOn() const
{
	return m_isEngineTurnOn;
}

bool CCar::TurnOnEngine()
{
	m_isEngineTurnOn = true;
	m_error = Error::NO_ERROR;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0)
	{
		m_isEngineTurnOn = false;
		m_error = Error::NO_ERROR;
		return true;
	}

	m_error = Error::ENGINE_CAN_NOT_BE_TURNED_OFF;
	return false;
}

bool CCar::SetGear(int gear)
{
	if (gear == 0)
	{
		m_gear = gear;
		m_error = Error::NO_ERROR;
		return true;
	}

	if (IsCorrectSpeedForGear(gear, static_cast<unsigned>(abs(m_speed))) && m_isEngineTurnOn)
	{
		if ((gear > 0 && m_speed >= 0) || (gear == -1 && m_speed == 0))
		{
			m_gear = gear;
			m_error = Error::NO_ERROR;
			return true;
		}
	}

	if (!m_isEngineTurnOn)
	{
		m_error = Error::ENGINE_IS_OFF;
	}
	else if ((gear == -1 && m_speed != 0) || (gear > 0 && GetDirection() == Direction::Backward))
	{
		m_error = Error::NO_ZERO_SPEED;
	}
	else
	{
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_GEAR;
	}
	return false;
}


bool CCar::SetSpeed(unsigned int speed)
{
	if (IsCorrectSpeedForGear(m_gear, speed))
	{
		(m_gear == -1) ? (m_speed = -1 * speed) : (m_speed = speed);
		m_error = Error::NO_ERROR;
		return true;
	}

	if (m_gear == 0 && m_isEngineTurnOn)
	{
		if (speed <= static_cast<unsigned>(abs(m_speed)))
		{
			(GetDirection() == Direction::Backward) ? (m_speed = -1 * speed) : (m_speed = speed);
			m_error = Error::NO_ERROR;
			return true;
		}

		m_error = Error::ONLY_REDUCE_THE_SPEED;
		return false;
	}

	if (!m_isEngineTurnOn)
		m_error = Error::ENGINE_IS_OFF;
	else if (m_gear == -1)
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_REVERSE_GEAR;
	else if (m_gear == 1)
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_FIRST_GEAR;
	else if (m_gear == 2)
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_SECOND_GEAR;
	else if (m_gear == 3)
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_THIRD_GEAR;
	else if (m_gear == 4)
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_FOURTH_GEAR;
	else
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_FIFTH_GEAR;

	return false;
}

int CCar::GetGear() const
{
	return m_gear;
}

unsigned int CCar::GetSpeed() const
{
	return abs(m_speed);
}

Direction CCar::GetDirection() const
{
	if (m_speed == 0)
	{
		return Direction::Stop;
	}
	else if (m_speed < 0)
	{
		return Direction::Backward;
	}
	else
	{
		return Direction::Forward;
	}
}

Error CCar::GetError() const
{
	return m_error;
}