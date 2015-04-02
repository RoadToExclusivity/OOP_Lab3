#include "stdafx.h"
#include "CustomFile.h"

const int CCustomFile::FILE_ERROR = -1;

CCustomFile::CCustomFile()
	:m_fileName(""), m_fileMode(""), m_isFileOpened(false), m_file(nullptr)
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
	return feof(m_file);
}

long int CCustomFile::GetLength() const
{
	
}

long int CCustomFile::GetPosition() const
{
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

}

bool CCustomFile::PutChar(char c)
{

}

bool CCustomFile::Seek(long int offset)
{

}

size_t CCustomFile::Write(const void *ptr, size_t size, size_t count)
{

}

size_t CCustomFile::Read(void *ptr, size_t size, size_t count)
{

}
