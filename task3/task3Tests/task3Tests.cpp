#include "stdafx.h"
#include "../task3/CustomFile.h"

struct FileFixture
{
	CCustomFile file;
	int data[10];

	FileFixture()
		:file()
	{

	}
};

BOOST_FIXTURE_TEST_SUITE(File, FileFixture)

BOOST_AUTO_TEST_CASE(NullptrFile)
{
	BOOST_CHECK(!file.IsOpened());
	BOOST_CHECK(file.GetChar() == CCustomFile::FILE_ERROR);
	BOOST_CHECK(file.GetLength() == CCustomFile::FILE_ERROR);
	BOOST_CHECK(file.GetPosition() == CCustomFile::FILE_ERROR);
	BOOST_CHECK(!file.Open());
	BOOST_CHECK(!file.PutChar('a'));
	BOOST_CHECK(!file.Seek(10));
	BOOST_CHECK(file.Read(data, sizeof(int), 10) == CCustomFile::FILE_ERROR);
	BOOST_CHECK(file.Write(data, sizeof(int), 10) == CCustomFile::FILE_ERROR);
}

BOOST_AUTO_TEST_SUITE_END()