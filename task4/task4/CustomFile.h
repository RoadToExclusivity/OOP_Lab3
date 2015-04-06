#pragma once
class CCustomFile
{
public:
	CCustomFile();
	CCustomFile(const char *fileName, const char *fileMode);
	~CCustomFile();

	static const int FILE_ERROR;

	bool IsOpened() const;
	bool IsEndOfFile() const;
	long GetLength() const;
	long GetPosition() const;

	bool Open();
	void Close();
	int GetChar();
	bool PutChar(char c);
	bool Seek(long offset);
	size_t Write(const void *ptr, size_t size, size_t count);
	size_t Read(void *ptr, size_t size, size_t count);

private:
	FILE* m_file;
	std::string m_fileName;
	std::string m_fileMode;
	bool m_isFileOpened;
};

