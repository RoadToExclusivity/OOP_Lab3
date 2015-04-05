#include "stdafx.h"
#include "../task4/MulticasedString.h"
#include "../task4/Address.h"

using namespace std;

const string ADDRESS = " ������, ���������, 37,  54";

struct AddressFixture
{
	CAddress address;

	AddressFixture()
		:address(ADDRESS)
	{
	}
};

//������ ��� ����, ����� ���������� ������
BOOST_AUTO_TEST_CASE(SetLocaleAddress)
{
	setlocale(LC_ALL, "rus");
}

BOOST_FIXTURE_TEST_SUITE(AddressTest, AddressFixture)

BOOST_AUTO_TEST_CASE(CheckEqualAddresses)
{
	BOOST_CHECK_EQUAL(address.IsEqualAddress(CAddress(",���������, 37, ")), true);
	BOOST_CHECK_EQUAL(address.IsEqualAddress(CAddress(",, ,  ")), true);
	BOOST_CHECK_EQUAL(address.IsEqualAddress(CAddress("������, ���������, 37,  54")), true);
	BOOST_CHECK_EQUAL(address.IsEqualAddress(CAddress("������,���������, 37, ")), true);
	BOOST_CHECK_EQUAL(address.IsEqualAddress(CAddress(",, 37,")), true);
}

BOOST_AUTO_TEST_CASE(CheckUnequalAddresses)
{
	BOOST_CHECK_EQUAL(address.IsEqualAddress(CAddress("���������, 37, ")), false);
	BOOST_CHECK_EQUAL(address.IsEqualAddress(CAddress("������-���, ���������, ,")), false);
	BOOST_CHECK_EQUAL(address.IsEqualAddress(CAddress(", 37,, ")), false);
}

BOOST_AUTO_TEST_SUITE_END()