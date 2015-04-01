#include "stdafx.h"
#include "../task2/Rectangle.h"

using namespace std;

const int WIDTH = 3, HEIGHT = 4;

struct RectangleFixture
{
	CRectangle rect;

	RectangleFixture() :
		rect(0, 0, WIDTH, HEIGHT)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture)

BOOST_AUTO_TEST_CASE(RectangleInitAndSetCheck)
{
	BOOST_CHECK(rect.GetLeftTop().x == 0);
	BOOST_CHECK(rect.GetLeftTop().y == 0);
	BOOST_CHECK(rect.GetRightBottom().x == 0 + WIDTH);
	BOOST_CHECK(rect.GetRightBottom().y == 0 + HEIGHT);
	BOOST_CHECK(rect.GetWidth() == WIDTH);
	BOOST_CHECK(rect.GetHeight() == HEIGHT);

	rect.SetWidth(7);
	rect.SetHeight(9);
	BOOST_CHECK(rect.GetWidth() == 7);
	BOOST_CHECK(rect.GetHeight() == 9);
	BOOST_CHECK(rect.GetArea() == 63);
	BOOST_CHECK(rect.GetPerimeter() == 32);

	rect.SetLeftTop(2, 2);
	BOOST_CHECK(rect.GetLeftTop().x == 2);
	BOOST_CHECK(rect.GetLeftTop().y == 2);
	BOOST_CHECK(rect.GetWidth() == 7 - (2 - 0));
	BOOST_CHECK(rect.GetHeight() == 9 - (2 - (0)));

	rect.SetRightBottom(1, 3);
	BOOST_CHECK(rect.GetWidth() == 0);
	BOOST_CHECK(rect.GetHeight() == 1);
}

BOOST_AUTO_TEST_CASE(RectangleInitWithWrongParams)
{
	CRectangle rectWrong(1, -1, -4, -2);
	BOOST_CHECK(rectWrong.GetWidth() == 0);
	BOOST_CHECK(rectWrong.GetHeight() == 0);
}

BOOST_AUTO_TEST_CASE(RectangleMoveAndScale)
{
	rect.Move(1, -1);
	BOOST_CHECK(rect.GetLeftTop().x == 1 + 0);
	BOOST_CHECK(rect.GetLeftTop().y == -1 + 0);
	BOOST_CHECK(rect.GetWidth() == WIDTH);
	BOOST_CHECK(rect.GetHeight() == HEIGHT);

	rect.Scale(2, 2);
	BOOST_CHECK(rect.GetLeftTop().x == 1 + 0);
	BOOST_CHECK(rect.GetLeftTop().y == -1 + 0);
	BOOST_CHECK(rect.GetWidth() == WIDTH * 2);
	BOOST_CHECK(rect.GetHeight() == HEIGHT * 2);

	rect.Scale(-2, 2);
	BOOST_CHECK(rect.GetLeftTop().x == 1 + 0);
	BOOST_CHECK(rect.GetLeftTop().y == -1 + 0);
	BOOST_CHECK(rect.GetWidth() == WIDTH * 2);
	BOOST_CHECK(rect.GetHeight() == HEIGHT * 2);
}

BOOST_AUTO_TEST_CASE(NoIntersectionWtihRectangle)
{
	CRectangle rect2(8, 8, 3, 3);
	BOOST_CHECK(!rect.Intersect(rect2));
	BOOST_CHECK(rect.GetWidth() == 0);
	BOOST_CHECK(rect.GetHeight() == 0);
}

BOOST_AUTO_TEST_CASE(RectangleIsInAnotherRectangle)
{
	CRectangle rect2(0, 0, 5, 6);
	BOOST_CHECK(rect.Intersect(rect2));
	BOOST_CHECK(rect.GetWidth() == WIDTH);
	BOOST_CHECK(rect.GetHeight() == HEIGHT);
	BOOST_CHECK(rect.GetLeftTop().x == 0);
	BOOST_CHECK(rect.GetLeftTop().y == 0);
}

BOOST_AUTO_TEST_CASE(RectangleHasIntersectionWithAnotherRectangle)
{
	CRectangle rect2(2, 1, 5, 6);
	BOOST_CHECK(rect.Intersect(rect2));
	BOOST_CHECK(rect.GetWidth() == 1);
	BOOST_CHECK(rect.GetHeight() == 3);
	BOOST_CHECK(rect.GetLeftTop().x == 2);
	BOOST_CHECK(rect.GetLeftTop().y == 1);
}

BOOST_AUTO_TEST_SUITE_END()