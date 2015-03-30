#include "stdafx.h"
#include "../task2/Rectangle.h"

using namespace std;

struct RectangleFixture
{
	CRectangle rect;
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture)

BOOST_AUTO_TEST_CASE(RectangleInitAndSetCheck)
{
	rect = CRectangle(1, -1, 3, 2);
	BOOST_CHECK(rect.GetLeftTop().x == 1);
	BOOST_CHECK(rect.GetLeftTop().y == -1);
	BOOST_CHECK(rect.GetRightBottom().x == 4);
	BOOST_CHECK(rect.GetRightBottom().y == 1);
	BOOST_CHECK(rect.GetWidth() == 3);
	BOOST_CHECK(rect.GetHeight() == 2);

	rect.SetHeight(9);
	rect.SetWidth(7);
	BOOST_CHECK(rect.GetWidth() == 7);
	BOOST_CHECK(rect.GetHeight() == 9);

	rect.SetLeftTop(2, 2);
	BOOST_CHECK(rect.GetLeftTop().x == 2);
	BOOST_CHECK(rect.GetLeftTop().y == 2);
	BOOST_CHECK(rect.GetWidth() == 7 - (2 - 1));
	BOOST_CHECK(rect.GetHeight() == 9 - (2 - (-1)));

	rect.SetRightBottom(1, 3);
	BOOST_CHECK(rect.GetWidth() == 0);
	BOOST_CHECK(rect.GetHeight() == 1);

}

BOOST_AUTO_TEST_CASE(RectangleWrongInit)
{
	rect = CRectangle(1, -1, -4, -2);
	BOOST_CHECK(rect.GetWidth() == 0);
	BOOST_CHECK(rect.GetHeight() == 0);
}

BOOST_AUTO_TEST_CASE(RectangleMoveAndScale)
{
	rect = CRectangle(0, 0, 10, 8);
	rect.Move(1, -1);
	BOOST_CHECK(rect.GetLeftTop().x == 1);
	BOOST_CHECK(rect.GetLeftTop().y == -1);
	BOOST_CHECK(rect.GetWidth() == 10);
	BOOST_CHECK(rect.GetHeight() == 8);

	rect.Scale(2, 2);
	BOOST_CHECK(rect.GetLeftTop().x == 1);
	BOOST_CHECK(rect.GetLeftTop().y == -1);
	BOOST_CHECK(rect.GetWidth() == 20);
	BOOST_CHECK(rect.GetHeight() == 16);

	rect.Scale(-2, 2);
	BOOST_CHECK(rect.GetLeftTop().x == 1);
	BOOST_CHECK(rect.GetLeftTop().y == -1);
	BOOST_CHECK(rect.GetWidth() == 20);
	BOOST_CHECK(rect.GetHeight() == 16);
}

BOOST_AUTO_TEST_SUITE_END()