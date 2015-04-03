#include "stdafx.h"
#include "CustomFile.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Not enough arguments\n");
		return 1;
	}

	CCustomFile fin(argv[1], "r"), fout(argv[2], "w");
	if (!fin.Open())
	{
		printf("Error with input file\n");
		return 0;
	}
	if (!fout.Open())
	{
		printf("Error with output file\n");
		return 0;
	}

	vector<char> dataFromFile;
	char c;
	while ((c = fin.GetChar()) != EOF)
	{
		dataFromFile.push_back(c);
	}
	reverse(dataFromFile.begin(), dataFromFile.end());

	for (auto c : dataFromFile)
	{
		fout.PutChar(c);
	}
	return 0;
}

