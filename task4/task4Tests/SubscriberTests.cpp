#include "stdafx.h"
#include "../task4/MulticasedString.h"
#include "../task4/Address.h"
#include "../task4/Name.h"
#include "../task4/Subscriber.h"

using namespace std;

const string NAME = "Иванов Сергей Петрович",
		ADDRESS = " Москва, Шаболовка, 37,  54";

struct SubFixture
{
	CSubscriber sub;
	
	SubFixture()
		:sub(NAME, ADDRESS)
	{
	}
};

//Только для того, чтобы установить локаль
BOOST_AUTO_TEST_CASE(SetLocaleSubscriber)
{
	setlocale(LC_ALL, "rus");
}

BOOST_FIXTURE_TEST_SUITE(SubTest, SubFixture)

BOOST_AUTO_TEST_CASE(CheckEqualNames)
{
	//BOOST_CHECK_EQUAL(sub.GetName(), "");
	/*BOOST_CHECK_EQUAL(name.IsEqualName(" Иванов  Сергей   "), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Сергей Петрович"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Иванов ПетровиЧ"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Иванов "), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Петрович"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Сергей Петрович Иванов"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Иванов Сергей Петрович"), true);*/
}

BOOST_AUTO_TEST_SUITE_END()