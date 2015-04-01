#include "stdafx.h"
#include "Canvas.h"
#include "Rectangle.h"

using namespace std;



int StringToInt(const char *str, bool &err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	return param;
}

int ReadNextNumber(stringstream &ss, bool &err)
{
	if (ss.eof())
	{
		err = true;
		return 0;
	}

	string num;
	getline(ss, num, ' ');
	return StringToInt(num.c_str(), err);
}

void DoAction(CRectangle &curRect, vector<CRectangle> &rectangles, const string &s)
{
	bool err = false;
	stringstream ss(s);
	string curAction;
	getline(ss, curAction, ' ');
	if (curAction == "Rectangle")
	{
		if (curRect.GetHeight() != 0 || curRect.GetWidth() != 0)
		{
			rectangles.push_back(curRect);
		}
		int left = ReadNextNumber(ss, err), top = ReadNextNumber(ss, err), width = ReadNextNumber(ss, err), height = ReadNextNumber(ss, err);
		if (!err)
		{
			CRectangle rect(left, top, width, height);
			curRect = rect;
		}
	}
	else
	{
		if (curAction == "Move")
		{
			int dx = ReadNextNumber(ss, err), dy = ReadNextNumber(ss, err);
			if (!err)
			{
				curRect.Move(dx, dy);
			}
		}
		else
		{
			if (curAction == "Scale")
			{
				int sx = ReadNextNumber(ss, err), sy = ReadNextNumber(ss, err);
				if (!err)
				{
					curRect.Scale(sx, sy);
				}
			}
			else
			{
				cout << s << " - unknown command" << endl;
				return;
			}
		}
	}

	if (err)
	{
		cout << s << " - wrong parameter" << endl;
	}
}

void PrintRectangleInfo(const CRectangle &rect)
{
	CPoint leftTop = rect.GetLeftTop(), rightBottom = rect.GetRightBottom();
	cout << "\t Left Top: (" << leftTop.x << "; " << leftTop.y << ")" << endl;
	cout << "\t Size: " << rect.GetWidth() << "*" << rect.GetHeight() << endl;;
	cout << "\t Right Bottom: (" << rightBottom.x << "; " << rightBottom.y << ")" << endl;
	cout << "\t Area: " << rect.GetArea() << endl;
	cout << "\t Perimeter: " << rect.GetPerimeter() << endl;
}

void FillRectangle(const CRectangle &rect, char code, CCanvas &canvas)
{
	CPoint leftTop = rect.GetLeftTop();
	for (size_t i = 0; i < rect.GetWidth(); ++i)
	{
		for (size_t j = 0; j < rect.GetHeight(); ++j)
		{
			canvas.SetPixel(i + leftTop.x, j + leftTop.y, code);
		}
	}
}

void PrintRectangles(ostream &os, CCanvas &canvas, const vector<CRectangle> &rectangles, const CRectangle &intersectRect)
{
	FillRectangle(rectangles[0], '+', canvas);
	if (rectangles.size() > 1)
	{
		FillRectangle(rectangles[1], '-', canvas);
		FillRectangle(intersectRect, '#', canvas);
	}
	canvas.Write(os);
}

bool ReadFromFile(const _TCHAR *fileName, CRectangle &rect, vector<CRectangle> &rectangles)
{
	ifstream fin(fileName);
	if (!fin)
	{
		return false;
	}

	string s;
	while (getline(fin, s))
	{
		DoAction(rect, rectangles, s);
	}
	if (rect.GetWidth() != 0 || rect.GetHeight() != 0)
	{
		rectangles.push_back(rect);
	}

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3)
	{
		cout << "Not enough arguments" << endl;
		return 1;
	}

	vector<CRectangle> rectangles;
	CRectangle rect = CRectangle();
	if (!ReadFromFile(argv[1], rect, rectangles))
	{
		cout << "Error with input file " << argv[1] << endl;
		return 0;
	}

	rect = CRectangle();
	if (!ReadFromFile(argv[2], rect, rectangles))
	{
		cout << "Error with input file " << argv[2] << endl;
	}

	if (rectangles.size() == 0)
	{
		return 0;
	}
	CRectangle intersectRect = rectangles[0];
	for (size_t i = 0; i < rectangles.size(); i++)
	{
		intersectRect.Intersect(rectangles[i]);
		cout << "Rectangle " << i + 1 << ":" << endl;
		PrintRectangleInfo(rectangles[i]);
	}
	cout << "Intersection rectangle:" << endl;
	PrintRectangleInfo(intersectRect);

	CCanvas canvas(60, 20);
	if (argc > 3)
	{
		ofstream of(argv[3]);
		PrintRectangles(of, canvas, rectangles, intersectRect);
	}
	else
	{
		PrintRectangles(cout, canvas, rectangles, intersectRect);
	}
	return 0;
}