#include "stdafx.h"
#include "Canvas.h"

bool ValidCoords(int x, int y, int maxX, int maxY)
{
	return !(x < 0 || y < 0 || x >= maxX || y >= maxY);
}

char CCanvas::m_nullSymbol = ' ';

CCanvas::CCanvas(unsigned width, unsigned height)
{
	m_width = width;
	m_height = height;
	
	m_canvas = new char*[width];
	for (unsigned i = 0; i < width; ++i)
	{
		m_canvas[i] = new char[height];
		memset(m_canvas[i], m_nullSymbol, height * sizeof(char));
	}
}

CCanvas::~CCanvas()
{
	for (unsigned i = 0; i < m_width; ++i)
	{
		delete[] m_canvas[i];
		m_canvas[i] = nullptr;
	}
	delete[] m_canvas;
	m_canvas = nullptr;
}

unsigned CCanvas::GetWidth() const
{
	return m_width;
}

unsigned CCanvas::GetHeight() const{	return m_height;}char CCanvas::GetPixel(int x, int y) const
{
	if (!ValidCoords(x, y, m_width, m_height))
	{
		return m_nullSymbol;
	}

	return m_canvas[x][y];
}

void CCanvas::Write(std::ostream &ostream) const{	for (unsigned i = 0; i < m_height; ++i)	{		for (unsigned j = 0; j < m_width; ++j)		{			ostream << m_canvas[j][i];		}		ostream << std::endl;	}}void CCanvas::Clear(char code)
{
	if (code < m_nullSymbol)
	{
		return;
	}

	for (unsigned i = 0; i < m_width; ++i)
	{
		memset(m_canvas[i], code, m_height * sizeof(char));
	}
}

void CCanvas::SetPixel(int x, int y, char code)
{
	if (code < m_nullSymbol || !ValidCoords(x, y, m_width, m_height))
	{
		return;
	}

	m_canvas[x][y] = code;
}
