#include "stdafx.h"
#include "../task4/MulticasedString.h"
#include "../task4/Name.h"

using namespace std;

const string NAME = "������ ������ ��������";

struct NameFixture
{
	CName name;

	NameFixture()
		:name(NAME)
	{
	}
};

//������ ��� ����, ����� ���������� ������
BOOST_AUTO_TEST_CASE(SetLocaleName)
{
	setlocale(LC_ALL, "rus");
}

BOOST_FIXTURE_TEST_SUITE(NameTest, NameFixture)

BOOST_AUTO_TEST_CASE(CheckEqualNames)
{
	BOOST_CHECK_EQUAL(name.IsEqualName(" ������ ������"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName(" ������  ������   "), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ ��������"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ ��������"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ "), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("��������"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ �������� ������"), true);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ ������ ��������"), true);
}

BOOST_AUTO_TEST_CASE(CheckUnequalNames)
{
	BOOST_CHECK_EQUAL(name.IsEqualName("������� ���� ��������"), false);
	BOOST_CHECK_EQUAL(name.IsEqualName("������ ���� ��������"), false);
	BOOST_CHECK_EQUAL(name.IsEqualName("����"), false);
	BOOST_CHECK_EQUAL(name.IsEqualName("���� ������ ���������"), false);
}

BOOST_AUTO_TEST_SUITE_END()