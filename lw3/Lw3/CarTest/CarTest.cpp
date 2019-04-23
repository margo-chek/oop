#include "pch.h"
#include "../Car/Car.h"
#include <sstream>
#include <functional>

void ExpectOperationSuccess(CCar &car, const std::function<bool(CCar &car)> &op, bool expectedEngineCondition, int expectedGear, int expectedSpeed, Direction expectedDirection)
{
	CHECK(op(car));
	CHECK(car.IsEngineTurnOn() == expectedEngineCondition);
	CHECK(car.GetGear() == expectedGear);
	CHECK(car.GetSpeed() == expectedSpeed);
	CHECK(car.GetDirection() == expectedDirection);
}

void ExpectOperationFailure(const CCar &car, const std::function<bool(CCar &car)> &op)
{
	auto clone(car);
	CHECK(!op(clone));
	CHECK(clone.IsEngineTurnOn() == car.IsEngineTurnOn());
	CHECK(clone.GetGear() == car.GetGear());
	CHECK(clone.GetSpeed() == car.GetSpeed());
	CHECK(clone.GetDirection() == car.GetDirection());
}

TEST_CASE("engine is turned off by default")
{
	//изначально двигатель выключен
	CCar car;

	ExpectOperationSuccess(car, [](CCar &car) { return !car.IsEngineTurnOn(); }, false /*Is engine turn on*/, 0 /*gear*/, 0 /*speed*/,
		Direction::Stop /*direction*/);
}

TEST_CASE("engine is off, only neutral gear can be selected")
{
	//при выключенном двигателе можно переключиться только на нейтральную передачу
	CCar car;

	ExpectOperationSuccess(car, [](CCar &car) { return car.SetGear(0); }, false /*Is engine turn on*/, 0 /*gear*/, 0 /*speed*/,
		Direction::Stop /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(1); });
}

TEST_CASE("do not change the speed with the engine off")
{
	//при выключенном двигателе нельзя изменить скорость
	CCar car;
	ExpectOperationFailure(car, [](CCar &car) { return car.SetSpeed(10); });
}

TEST_CASE("engine can be turned on")
{
	//двигатель может быть включен
	CCar car;
	ExpectOperationSuccess(car, [](CCar& car) { return car.TurnOnEngine(); }, true /*Is engine turn on*/, 0 /*gear*/, 0 /*speed*/,
		Direction::Stop /*direction*/);
}

TEST_CASE("engine is on, can turn on gear, if the speed corresponds to the gear")
{
	//при включенном двигателе можно выбрать передачу, соответствующую скорости
	CCar car;
	car.TurnOnEngine();

	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(-1); }, true /*Is engine turn on*/, -1 /*gear*/, 0 /*speed*/,
		Direction::Stop /*direction*/);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(0); }, true /*Is engine turn on*/, 0 /*gear*/, 0 /*speed*/,
		Direction::Stop /*direction*/);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(1); }, true /*Is engine turn on*/, 1 /*gear*/, 0 /*speed*/,
		Direction::Stop /*direction*/);
	
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(2); });
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(-2); });
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(6); });

	car.SetSpeed(20);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(2); }, true /*Is engine turn on*/, 2 /*gear*/, 20 /*speed*/,
		Direction::Forward /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(3); });
	car.SetSpeed(30);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(3); }, true /*Is engine turn on*/, 3 /*gear*/, 30 /*speed*/,
		Direction::Forward /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(4); });
	car.SetSpeed(40);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(4); }, true /*Is engine turn on*/, 4 /*gear*/, 40 /*speed*/,
		Direction::Forward /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(5); });
	car.SetSpeed(50);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(5); }, true /*Is engine turn on*/, 5 /*gear*/, 50 /*speed*/,
		Direction::Forward /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(1); });
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(0); }, true /*Is engine turn on*/, 0 /*gear*/, 50 /*speed*/,
		Direction::Forward /*direction*/);
}

TEST_CASE("engine is on, can change on gear, if the gear corresponds to the speed")
{
	//при включенном двигателе можно менять скорость при соответствующей передаче
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetSpeed(30); }, true /*Is engine turn on*/, 1 /*gear*/, 30 /*speed*/,
		Direction::Forward /*direction*/);
	car.SetGear(2);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetSpeed(50); }, true /*Is engine turn on*/, 2 /*gear*/, 50 /*speed*/,
		Direction::Forward /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetSpeed(19); });
	car.SetGear(3);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetSpeed(60); }, true /*Is engine turn on*/, 3 /*gear*/, 60 /*speed*/,
		Direction::Forward /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetSpeed(29); });
	car.SetGear(4);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetSpeed(90); }, true /*Is engine turn on*/, 4 /*gear*/, 90 /*speed*/,
		Direction::Forward /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetSpeed(39); });
	car.SetGear(5);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetSpeed(150); }, true /*Is engine turn on*/, 5 /*gear*/, 150 /*speed*/,
		Direction::Forward /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetSpeed(151); });
	car.SetGear(0);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetSpeed(90); }, true /*Is engine turn on*/, 0 /*gear*/, 90 /*speed*/,
		Direction::Forward /*direction*/);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetSpeed(100); });
}

TEST_CASE("can switch to reverse gear only at zero speed")
{
	//на задний ход можно переключиться только на нулевой скорости
	CCar car;
	car.TurnOnEngine();
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(-1); }, true /*Is engine turn on*/, -1 /*gear*/, 0 /*speed*/,
		Direction::Stop /*direction*/);
	car.SetSpeed(10);
	car.SetGear(0);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(-1); });
	car.SetSpeed(0);
	car.SetGear(1);
	car.SetSpeed(10);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(-1); });
}

TEST_CASE("from reverse gear can switch to first gear only at zero speed")
{
	//с заднего хода можно переключиться на первую передачу только на нулевой скорости
	CCar car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(1); });
	car.SetGear(0);
	ExpectOperationFailure(car, [](CCar &car) { return car.SetGear(1); });
	car.SetSpeed(0);
	ExpectOperationSuccess(car, [](CCar& car) { return car.SetGear(1); }, true /*Is engine turn on*/, 1 /*gear*/, 0 /*speed*/,
		Direction::Stop /*direction*/);
}

TEST_CASE("engine can be turned off in neutral gear and at zero speed")
{
	//двигатель может быть выключен только на нейтральной передаче и при нулевой скорости
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	ExpectOperationFailure(car, [](CCar &car) { return car.TurnOffEngine(); });
	car.SetSpeed(0);
	car.SetGear(0);
	ExpectOperationSuccess(car, [](CCar& car) { return car.TurnOffEngine(); }, false /*Is engine turn on*/, 0 /*gear*/, 0 /*speed*/,
		Direction::Stop /*direction*/);
}