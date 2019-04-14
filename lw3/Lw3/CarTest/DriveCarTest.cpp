#include "pch.h"
#include "../Car/DriveCar.h"
#include "../Car/Car.h"
#include <sstream>

void VerifyCommandHandling(CCar &car, const std::string &command, const std::string &expectedOutput)
{
	std::stringstream output, input;
	output = std::stringstream();
	input = std::stringstream();
	CDriveCar driverCar(car, input, output);

	CHECK(input << command);
	CHECK(driverCar.ExecuteCommand());
	CHECK(input.eof());
	CHECK(output.str() == expectedOutput);
}

TEST_CASE("can handle EngineOn command")
{
	CCar car;
	VerifyCommandHandling(car, "EngineOn", "Engine is turned on\n");
};

TEST_CASE("can handle EngineOff command")
{
	CCar car;
	VerifyCommandHandling(car, "EngineOff", "Engine is turned off\n");
};

TEST_CASE("can print car info")
{
	CCar car;
	VerifyCommandHandling(car, "Info",
		R"(Engine is turned off
Speed 0
Direction stop
Gear 0
)");
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	VerifyCommandHandling(car, "Info",
		R"(Engine is turned on
Speed 20
Direction forward
Gear 1
)");
};

TEST_CASE("can't select gear when engine is turned off")
{
	CCar car;
	VerifyCommandHandling(car, "SetGear 1",
		R"(Gear did not change
Engine is off
)");
};

TEST_CASE("can select a valid gear when engine is on")
{
	CCar car;
	car.TurnOnEngine();
	VerifyCommandHandling(car, "SetGear 1", "Selected gear 1\n");
};

TEST_CASE("can't select an incorrect gear")
{
	CCar car;
	VerifyCommandHandling(car, "SetGear a", "Invalid gear\n");
};

TEST_CASE("can't select a gear out of range")
{
	CCar car;
	car.TurnOnEngine();
	VerifyCommandHandling(car, "SetGear -2", "Use a gear between -1 and 5\n");
	VerifyCommandHandling(car, "SetGear 6", "Use a gear between -1 and 5\n");
};

TEST_CASE("can't change speed when engine is turned off")
{
	CCar car;
	VerifyCommandHandling(car, "SetSpeed 10",
		R"(Speed did not change
Engine is off
)");
};

TEST_CASE("can change speed when engine is on and gear is not zero")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	VerifyCommandHandling(car, "SetSpeed 20", "Selected speed 20\n");
};

TEST_CASE("can't select an incorrect speed")
{
	CCar car;
	VerifyCommandHandling(car, "SetSpeed a", "Invalid speed\n");
};


TEST_CASE("can't select a nagative speed")
{
	CCar car;
	VerifyCommandHandling(car, "SetSpeed -2", "Speed can not be negative\n");
};

