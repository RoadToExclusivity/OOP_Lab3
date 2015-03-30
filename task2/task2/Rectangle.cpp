#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(int x, int y, int width, int height)
{
	if (width < 0)
	{
		width = 0;
	}
	if (height < 0)
	{
		height = 0;
	}

	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}


CRectangle::~CRectangle()
{
}

size_t CRectangle::GetWidth() const
{
	return m_width;
}

size_t CRectangle::GetHeight() const
{
	return m_height;
}

CPoint CRectangle::GetLeftTop() const
{
	return CPoint(m_x, m_y);
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_x + m_width, m_y + m_height);
}

size_t CRectangle::Area() const
{
	return m_width * m_height;
}

size_t CRectangle::Perimeter() const
{
	return 2 * (m_width + m_height);
}

void CRectangle::SetWidth(int width)
{
	if (width < 0)
	{
		width = 0;
	}

	m_width = width;
}

void CRectangle::SetHeight(int height)
{
	if (height < 0)
	{
		height = 0;
	}

	m_height = height;
}

void CRectangle::SetLeftTop(int x, int y)
{
	m_width += m_x - x;
	m_height += m_y - y;

	if (m_width < 0)
	{
		m_width = 0;
	}
	if (m_height < 0)
	{
		m_height = 0;
	}

	m_x = x;
	m_y = y;
}

void CRectangle::SetRightBottom(int x, int y)
{
	int newWidth = m_width + (x - (m_x + m_width));
	int newHeight = m_height + (y - (m_y + m_height));

	if (newWidth < 0)
	{
		newWidth = 0;
	}
	if (newHeight < 0)
	{
		newHeight = 0;
	}

	m_width = newWidth;
	m_height = newHeight;
}

void CRectangle::Move(int dx, int dy)
{
	m_x += dx;
	m_y += dy;
}

void CRectangle::Scale(int sx, int sy)
{
	if (sx < 0 || sy < 0)
	{
		return;
	}

	m_width *= sx;
	m_height *= sy;
}

bool CRectangle::Intersect(const CRectangle &other)
{
	int lx = m_x, ly = m_y;
	int rx = m_x + m_width, ry = m_y + m_height;
	int lx1 = other.m_x, ly1 = other.m_y;
	int rx1 = lx1 + other.m_width, ry1 = ly1 + other.m_height;
	
	int minX = std::max(lx, lx1), maxX = std::min(rx, rx1);
	int minY = std::max(ly, ly1), maxY = std::min(ry, ry1);
	if (maxX > minX && maxY > minY)
	{
		m_x = minX;
		m_y = minY;
		m_width = maxX - minX;
		m_height = maxY - minY;
		return true;
	}

	m_width = 0;
	m_height = 0;
	return false;
}