#include "stdafx.h"
#include "../task4/MulticasedString.h"
#include "../task4/Address.h"
#include "../task4/Name.h"
#include "../task4/Subscriber.h"

using namespace std;

const string NAME = "������ ������ ��������",
		ADDRESS = " ������, ���������, 37,  54";

struct SubFixture
{
	CSubscriber sub;
	
	SubFixture()
		:sub(NAME, ADDRESS)
	{
	}
};

//������ ��� ����, ����� ���������� ������
BOOST_AUTO_TEST_CASE(SetLocaleSubscriber)
{
	setlocale(LC_ALL, "rus");
}

BOOST_FIXTURE_TEST_SUITE(SubTest, SubFixture)

BOOST_AUTO_TEST_CASE(CheckEqualNames)
{
	//BOOST_CHECK_EQUAL(sub.GetName(), "");
	/*BOOST_CHECK_EQUAL(name.IsEqualName(" ������  ������   "), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ ��������"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ ��������"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ "), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("��������"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ �������� ������"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ ������ ��������"), true);*/
}

BOOST_AUTO_TEST_SUITE_END()