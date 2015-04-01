#pragma once
class CCanvas
{
public:
	CCanvas(unsigned width, unsigned height);
	~CCanvas();

	unsigned GetWidth() const;
	unsigned GetHeight() const;
	void Write(std::ostream &ostream) const;
	void SetPixel(int x, int y, char code);
	char **m_canvas;
	static char m_nullSymbol;
	unsigned m_width;
	unsigned m_height;
};
