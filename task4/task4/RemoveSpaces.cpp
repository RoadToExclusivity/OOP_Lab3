#include "stdafx.h"
#include "RemoveSpaces.h"

using namespace std;

string RemoveExtraSpaces(const string &arg)
{
	string newString = "";
	size_t lastIndex = arg.find_last_not_of(' ');
	if (lastIndex != string::npos)
	{
		bool wasSpace = true;
		for (size_t i = 0; i <= lastIndex; ++i)
		{
			if (arg[i] == ' ')
			{
				if (!wasSpace)
				{
					newString += arg[i];
					wasSpace = true;
				}
			}
			else
			{
				wasSpace = false;
				newString += arg[i];
			}
		}
	}

	return newString;
}