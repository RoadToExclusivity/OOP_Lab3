#pragma once

struct CPoint
{
	CPoint() 
		:x(0), y(0)
	{

	}

	CPoint(int x0, int y0) 
		:x(x0), y(y0)
	{

	}

	int x;
	int y;
};

class CRectangle
{
public:

	CRectangle();
	CRectangle(int x, int y, int width, int height);
	~CRectangle();

	size_t GetWidth() const;
	size_t GetHeight() const;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	size_t Area() const;
	size_t Perimeter() const;

	void SetWidth(int width);
	void SetHeight(int height);
	void SetLeftTop(int x, int y);
	void SetRightBottom(int x, int y);

	void Move(int dx, int dy);
	void Scale(int sx, int sy);
	bool Intersect(const CRectangle &other);

private:
	int m_x, m_y;
	size_t m_width, m_height;
};

