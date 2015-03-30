#include "stdafx.h"
#include "Car.h"

using namespace std;

int StringToInt(const char *str, bool &err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	return param;
}

void PrintInfo(const CCar &c)
{
	cout << "Engine is ";
	if (c.IsEngineTurnedOn())
	{
		cout << "turned on" << endl;
	}
	else
	{
		cout << "turned off" << endl;
		return;
	}

	CCar::direction d = c.GetDirection();
	switch (d)
	{
	case CCar::BACKWARD:
		cout << "Car is moving backward" << endl;
		break;
	case CCar::STAY:
		cout << "Car is staying" << endl;
		break;
	case CCar::FORWARD:
		cout << "Car is moving forward" << endl;
		break;
	}

	cout << "Speed = " << c.GetSpeed() << endl;

	cout << "Gear = " << c.GetGear() << endl;
}

void DoAction(CCar &car, const string &s)
{
	if (s == "Info")
	{
		PrintInfo(car);
	}
	else
	{
		if (s == "EngineOn")
		{
			if (!car.TurnOnEngine())
			{
				cout << "Unable to turn engine on" << endl;
			}
		}
		else
		{
			if (s == "EngineOff")
			{
				if (!car.TurnOffEngine())
				{
					cout << "Unable to turn engine off" << endl;
				}
			}
			else
			{
				string tryGear = s.substr(0, 8), trySpeed = s.substr(0, 9), numString = "";
				bool err;
				if (tryGear == "SetGear " && s != tryGear)
				{
					numString = s.substr(8);
					int gear = StringToInt(numString.c_str(), err);
					if (!err)
					{
						if (!car.SetGear(gear))
						{
							cout << "Setting gear was failed" << endl;
						}
					}
				}
				else
				{
					if (trySpeed == "SetSpeed " && s != trySpeed)
					{
						numString = s.substr(9);
						int speed = StringToInt(numString.c_str(), err);
						if (!err)
						{
							if (!car.SetSpeed(speed))
							{
								cout << "Setting speed was failed" << endl;
							}
						}
					}
					else
					{
						cout << "Unknown command" << endl;
					}
				}
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CCar car;
	string s;
	cout << "Command: ";
	while (getline(cin, s))
	{
		DoAction(car, s);
		cout << "Command: ";
	}
	return 0;
}

