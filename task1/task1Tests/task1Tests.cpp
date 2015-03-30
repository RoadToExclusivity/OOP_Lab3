#include "stdafx.h"
#include "../task1/Car.h"

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

BOOST_AUTO_TEST_CASE(CarIsInactiveByDefault)
{
	BOOST_CHECK(!car.IsEngineTurnedOn());
	BOOST_CHECK(car.GetDirection() == CCar::STAY);
	BOOST_CHECK(car.GetGear() == 0);
	BOOST_CHECK(car.GetSpeed() == 0);
}

BOOST_AUTO_TEST_CASE(SimpleMoveCar)
{
	BOOST_CHECK(!car.SetGear(1));
	
	BOOST_CHECK(car.TurnOnEngine());
	BOOST_CHECK(!car.SetGear(111));
	BOOST_CHECK(car.SetGear(1));
	BOOST_CHECK(car.SetGear(1));
	BOOST_CHECK(car.SetSpeed(30));
	BOOST_CHECK(car.GetDirection() == CCar::FORWARD);

	BOOST_CHECK(!car.SetSpeed(60));
	BOOST_CHECK(car.SetGear(3));
	BOOST_CHECK(car.SetSpeed(60));
	BOOST_CHECK(car.GetDirection() == CCar::FORWARD);

	BOOST_CHECK(!car.TurnOffEngine());
}

BOOST_AUTO_TEST_CASE(MovingBackwards)
{
	car.TurnOnEngine();
	BOOST_CHECK(car.SetGear(0));
	BOOST_CHECK(!car.SetSpeed(20));

	BOOST_CHECK(car.SetGear(-1));
	BOOST_CHECK(!car.SetSpeed(40));
	BOOST_CHECK(car.SetSpeed(20));
	BOOST_CHECK(car.GetDirection() == CCar::BACKWARD);

	BOOST_CHECK(car.SetGear(0));
	BOOST_CHECK(car.SetSpeed(0));
	BOOST_CHECK(car.TurnOffEngine());
}

BOOST_AUTO_TEST_CASE(MovingBackwardAndForward)
{
	car.TurnOnEngine();
	BOOST_CHECK(car.SetGear(-1));

	BOOST_CHECK(car.SetGear(1));
	BOOST_CHECK(car.SetGear(-1));

	BOOST_CHECK(car.SetGear(-1));
	BOOST_CHECK(car.SetSpeed(20));
	BOOST_CHECK(car.GetDirection() == CCar::BACKWARD);

	BOOST_CHECK(!car.SetGear(1));
	BOOST_CHECK(car.SetSpeed(0));
	BOOST_CHECK(car.SetGear(1));
	BOOST_CHECK(car.GetDirection() == CCar::STAY);

	BOOST_CHECK(car.SetSpeed(10));
	BOOST_CHECK(car.GetDirection() == CCar::FORWARD);
}

BOOST_AUTO_TEST_CASE(MovingBackwardToNeutralOnSpeed)
{
	car.TurnOnEngine();
	BOOST_CHECK(car.SetGear(-1));
	BOOST_CHECK(car.SetSpeed(20));

	BOOST_CHECK(!car.SetGear(1));
	BOOST_CHECK(car.SetGear(0));

	BOOST_CHECK(!car.SetGear(1));
	BOOST_CHECK(car.SetSpeed(0));
	BOOST_CHECK(car.SetGear(1));

	BOOST_CHECK(car.SetSpeed(10));
	BOOST_CHECK(!car.SetGear(-1));
	BOOST_CHECK(car.SetSpeed(0));
	BOOST_CHECK(car.SetGear(-1));
}

BOOST_AUTO_TEST_SUITE_END()