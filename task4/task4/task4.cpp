#include "stdafx.h"
#include "AddressBook.h"
#include "CustomFile.h"
#include "Address.h"
#include "Name.h"
#include "Subscriber.h"

using namespace std;

const char *DATABASE_NAME = "db.txt";

bool IsValidName()
{
	
}

void GetSearchData(CName &name, CAddress &address, string &phoneNumber, string &email)
{
	string sName;
	cout << "Имя абонента: " << endl;
	cin >> sName;

	string sAddress;
	cout << "Адрес абонента: " << endl;
	cin >> sName;

	string sPhoneNumber;
	cout << "Мобильный телефон абонента: " << endl;
	cin >> sName;

	string sEmail;
	cout << "Электронная почта абонента: " << endl;
	cin >> sName;
}

bool GetNewSubData(string &name, string &address, string &phoneNumber, string &email)
{
	string sName;
	cout << "Имя абонента: ";
	cin >> sName;
	name = sName;

	string sAddress;
	cout << "Адрес абонента: ";
	cin >> sAddress;
	address = sAddress;

	string sPhoneNumber;
	cout << "Мобильный телефон абонента: ";
	cin >> sPhoneNumber;
	phoneNumber = sPhoneNumber;

	string sEmail;
	cout << "Электронная почта абонента: ";
	cin >> sEmail;
	email = sEmail;

	return true;
}

void PrintMainActions()
{
	cout << "Выберите действие:" << endl;
	cout << "1. Поиск абонента" << endl;
	cout << "2. Добавить абонента" << endl;
	cout << "3. Отредактировать/удалить абонента" << endl;
	cout << "Q. Выйти" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	CAddressBook book;
	
	CCustomFile dbForRead(DATABASE_NAME, "r"), dbForWrite(DATABASE_NAME, "w");
	
	dbForRead.Open();
	book.LoadSubCollection(dbForRead);
	dbForRead.Close();

	CSubscriberCollection collection;
	book.GetSubCollection(collection);

	char c = '`';
	PrintMainActions();
	while ((c = getchar()) != EOF)
	{
		string name, address;
		string phoneNumber = "", email = "";

		if (c == 'Q')
		{
			break;
		}
		switch (c)
		{
			case '1':
				break;
			case '2':
				if (GetNewSubData(name, address,phoneNumber, email))
				{
					CSubscriber sub(name, address, phoneNumber, email);
					if (!collection.AddSub(sub))
					{
						cout << "Невозможно добавить абонента!" << endl;
					}
				}
				break;
			case '3':
				break;
			default:
				break;
		}
		PrintMainActions();
	}
	
	book.SetSubCollection(collection);
	dbForWrite.Open();
	book.SaveSubCollecton(dbForWrite);
	return 0;
}

