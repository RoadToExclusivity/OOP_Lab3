#pragma once
class CCanvas
{
public:
	CCanvas(unsigned width, unsigned height);
	~CCanvas();

	unsigned GetWidth() const;
	unsigned GetHeight() const;	char GetPixel(int x, int y) const;
	void Write(std::ostream &ostream) const;	void Clear(char code = m_nullSymbol);
	void SetPixel(int x, int y, char code);private:
	char **m_canvas;
	static char m_nullSymbol;
	unsigned m_width;
	unsigned m_height;
};

