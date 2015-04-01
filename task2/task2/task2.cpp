#include "stdafx.h"
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

void DoAction(ofstream &fout, CRectangle &curRect, vector<CRectangle> &rectangles, const string &s)
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

void PrintRectangle(ofstream &fout, const CRectangle &rect)
{
	CPoint leftTop = rect.GetLeftTop(), rightBottom = rect.GetRightBottom();
	fout << "\t Left Top: (" << leftTop.x << "; " << leftTop.y << ")" << endl;
	fout << "\t Size: " << rect.GetWidth() << "*" << rect.GetHeight() << endl;;
	fout << "\t Right Bottom: (" << rightBottom.x << "; " << rightBottom.y << ")" << endl;
	fout << "\t Area: " << rect.GetArea() << endl;
	fout << "\t Perimeter: " << rect.GetPerimeter() << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3)
	{
		cout << "Not enough arguments" << endl;
		return 1;
	}

	ifstream fin(argv[1]);
	if (!fin)
	{
		cout << "Error with input file" << endl;
		return 1;
	}
	ofstream fout(argv[2]);
	if (!fout)
	{
		cout << "Error with output file" << endl;
		return 1;
	}

	string s;
	vector<CRectangle> rectangles;
	CRectangle rect(0, 0, 0, 0);
	while (getline(fin, s))
	{
		DoAction(fout, rect, rectangles, s);
	}

	if (rectangles.size() == 0 && rect.GetWidth() == 0 && rect.GetHeight() == 0)
	{
		return 0;
	}
	
	rectangles.push_back(rect);
	CRectangle intersectRect = rectangles[0];
	for (size_t i = 0; i < rectangles.size(); i++)
	{
		intersectRect.Intersect(rectangles[i]);
		fout << "Rectangle " << i + 1 << ":" << endl;
		PrintRectangle(fout, rectangles[i]);
	}
	fout << "Intersection rectangle:" << endl;
	PrintRectangle(fout, intersectRect);

	return 0;
}

