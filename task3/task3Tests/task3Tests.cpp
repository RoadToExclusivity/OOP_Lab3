#include "stdafx.h"
#include "../task3/CustomFile.h"

const char *FILE_NAME = "input.txt";
const int DATA_SIZE = 5;
const int DATA[] = { 0, 1, 2, 3, 4 };

struct NullFileFixture
{
	CCustomFile file;

	int data[DATA_SIZE];

	NullFileFixture()
		:file()
	{

	}
};

struct WriteFileFixture
{
	CCustomFile file;

	WriteFileFixture()
		:file(FILE_NAME, "wb")
	{

	}
};

struct ReadFileFixture
{
	CCustomFile file;
	int data[10];

	ReadFileFixture()
		:file(FILE_NAME, "rb")
	{

	}
};

BOOST_FIXTURE_TEST_SUITE(NullFile, NullFileFixture)

BOOST_AUTO_TEST_CASE(NullptrFile)
{
	BOOST_CHECK(!file.IsOpened());
	BOOST_CHECK(!file.IsEndOfFile());
	BOOST_CHECK_EQUAL(file.GetChar(), CCustomFile::FILE_ERROR);
	BOOST_CHECK_EQUAL(file.GetLength(), CCustomFile::FILE_ERROR);
	BOOST_CHECK_EQUAL(file.GetPosition(), CCustomFile::FILE_ERROR);
	BOOST_CHECK(!file.Open());
	BOOST_CHECK(!file.PutChar('a'));
	BOOST_CHECK(!file.Seek(10));
	BOOST_CHECK_EQUAL(file.Read(data, sizeof(int), DATA_SIZE), CCustomFile::FILE_ERROR);
	BOOST_CHECK_EQUAL(file.Write(DATA, sizeof(int), DATA_SIZE), CCustomFile::FILE_ERROR);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(WriteFile, WriteFileFixture)

BOOST_AUTO_TEST_CASE(WriteFileOperationsCheck)
{
	BOOST_CHECK(!file.IsOpened());
	BOOST_CHECK(file.Open());
	BOOST_CHECK_EQUAL(file.GetLength(), 0);
	BOOST_CHECK(file.PutChar('q'));
	BOOST_CHECK_EQUAL(file.Write(DATA, sizeof(int), DATA_SIZE), DATA_SIZE);
	BOOST_CHECK(file.Seek(0));
	BOOST_CHECK(file.PutChar('w'));
	BOOST_CHECK_EQUAL(file.GetPosition(), 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(ReadFile, ReadFileFixture)

BOOST_AUTO_TEST_CASE(ReadFileOperationsCheck)
{
	BOOST_CHECK(!file.IsOpened());
	BOOST_CHECK(file.Open());
	BOOST_CHECK(!file.PutChar('q'));
	BOOST_CHECK_EQUAL(file.GetLength(), 21);

	int ch1 = file.GetChar();
	BOOST_CHECK_EQUAL(ch1, 'w');

	BOOST_CHECK_EQUAL(file.Read(data, sizeof(int), DATA_SIZE), DATA_SIZE);
	for (size_t i = 0; i < DATA_SIZE; ++i)
	{
		BOOST_CHECK_EQUAL(data[i], DATA[i]);
	}
	BOOST_CHECK_EQUAL(file.GetChar(), EOF);
	BOOST_CHECK(file.IsEndOfFile());
}

BOOST_AUTO_TEST_SUITE_END()