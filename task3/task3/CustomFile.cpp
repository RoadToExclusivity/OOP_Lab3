#include "stdafx.h"
#include "CustomFile.h"

const int CCustomFile::FILE_ERROR = EOF - 0x2015;

CCustomFile::CCustomFile()
	:m_fileName(""), m_fileMode("r"), m_isFileOpened(false), m_file(nullptr)
{
}

CCustomFile::CCustomFile(const char *fileName, const char *fileMode)
	: m_fileName(fileName), m_fileMode(fileMode), m_isFileOpened(false), m_file(nullptr)
{
}

CCustomFile::~CCustomFile()
{
	Close();
	m_file = nullptr;
}

bool CCustomFile::IsOpened() const
{
	return m_isFileOpened;
}

bool CCustomFile::IsEndOfFile() const
{
	return m_isFileOpened && feof(m_file);
}

long CCustomFile::GetLength() const
{
	return FILE_ERROR;
}

long CCustomFile::GetPosition() const
{
	if (!m_isFileOpened)
	{
		return FILE_ERROR;
	}

	long res = ftell(m_file);
	if (res != -1L)
	{
		return res;
	}

	return FILE_ERROR;
}

bool CCustomFile::Open()
{
	if (m_isFileOpened)
	{
		Close();
	}

	if (m_fileMode == "")
	{
		return false;
	}

	if (!(m_file = fopen(m_fileName.c_str(), m_fileMode.c_str())))
	{
		return false;
	}
	
	return true;
}

void CCustomFile::Close()
{
	if (m_isFileOpened)
	{
		fclose(m_file);
	}
}

int CCustomFile::GetChar()
{
	if (!m_isFileOpened)
	{
		return FILE_ERROR;
	}

	int res = fgetc(m_file);
	if (ferror(m_file))
	{
		return FILE_ERROR;
	}
	
	return res;
}

bool CCustomFile::PutChar(char c)
{
	if (!m_isFileOpened)
	{
		return false;
	}

	fputc(c, m_file);
	if (ferror(m_file))
	{
		return false;
	}

	return true;
}

bool CCustomFile::Seek(long offset)
{
	if (!m_isFileOpened)
	{
		return false;
	}

	return fseek(m_file, offset, SEEK_SET);
}

size_t CCustomFile::Write(const void *ptr, size_t size, size_t count)
{
	if (!m_isFileOpened)
	{
		return FILE_ERROR;
	}

	size_t res = fwrite(ptr, size, count, m_file);
	if (ferror(m_file))
	{
		return FILE_ERROR;
	}

	return res;
}

size_t CCustomFile::Read(void *ptr, size_t size, size_t count)
{
	if (!m_isFileOpened)
	{
		return FILE_ERROR;
	}

	size_t res = fread(ptr, size, count, m_file);
	if (ferror(m_file))
	{
		return FILE_ERROR;
	}

	return res;
}
