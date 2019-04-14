#pragma once

enum class Direction
{
	Backward,
	Stop,
	Forward
};

enum class Error
{
	NO_ERROR,
	ENGINE_IS_OFF,
	ENGINE_CAN_NOT_BE_TURNED_OFF,
	NO_ZERO_SPEED,
	SPEED_IS_NOT_CORRECT_FOR_GEAR,
	ONLY_REDUCE_THE_SPEED,
	SPEED_IS_NOT_CORRECT_FOR_REVERSE_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_FIRST_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_SECOND_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_THIRD_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_FOURTH_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_FIFTH_GEAR
};

class CCar
{
public:
	bool IsEngineTurnOn() const;
	int GetGear() const;
	unsigned int GetSpeed() const;
	Direction GetDirection() const;
	Error GetError() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(unsigned int speed);
private:
	bool m_isEngineTurnOn = false;
	int m_gear = 0;
	int m_speed = 0;
	Error m_error = Error::NO_ERROR;
};


