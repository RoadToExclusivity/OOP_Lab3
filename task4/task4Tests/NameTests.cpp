#include "stdafx.h"
#include "../task4/MulticasedString.h"
#include "../task4/Name.h"

using namespace std;

const string NAME = "Иванов Сергей Петрович";

struct NameFixture
{
	CName name;

	NameFixture()
		:name(NAME)
	{
	}
};

//Только для того, чтобы установить локаль
BOOST_AUTO_TEST_CASE(SetLocaleName)
{
	setlocale(LC_ALL, "rus");
}

BOOST_FIXTURE_TEST_SUITE(NameTest, NameFixture)

BOOST_AUTO_TEST_CASE(CheckEqualNames)
{
	BOOST_CHECK_EQUAL(name.IsEqualName(" Сергей иванов"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName(" Иванов  Сергей   "), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Сергей Петрович"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Иванов ПетровиЧ"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Иванов "), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Петрович"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Сергей Петрович Иванов"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("Иванов Сергей Петрович"), true);
}

BOOST_AUTO_TEST_CASE(CheckUnequalNames)
{
	BOOST_CHECK_EQUAL(name.IsEqualName("Сергеев Иван Петрович"), false);
	BOOST_CHECK_EQUAL(name.IsEqualName("Иванов Иван Петрович"), false);
	BOOST_CHECK_EQUAL(name.IsEqualName("Иван"), false);
	BOOST_CHECK_EQUAL(name.IsEqualName("Семён Семёныч Горбунков"), false);
}

BOOST_AUTO_TEST_SUITE_END()