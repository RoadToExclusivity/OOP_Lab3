#include "stdafx.h"
#include "AddressBook.h"
#include "Address.h"
#include "Name.h"
#include "Subscriber.h"

using namespace std;

const char *DATABASE_NAME = "db.txt";

bool IsValidName(const string &s)
{
	bool res;
	for (auto c : s)
	{
		if (!isalpha(c))
		{
			res = false;
			break;
		}
	}

	return res;
}

bool IsValidNumber(const string &s)
{
	bool res;
	for (auto c : s)
	{
		if (!isdigit(c))
		{
			res = false;
			break;
		}
	}

	return res;
}

bool GetSubData(string &name, string &address, string &phoneNumber, string &email)
{
	string sName;
	cout << "Имя абонента: ";
	cin >> sName;
	if (!IsValidName(sName) && sName != "")
	{
		return false;
	}
	name = sName;

	string sAddress;
	cout << "Адрес абонента: ";
	cin >> sAddress;
	address = sAddress;

	string sPhoneNumber;
	cout << "Мобильный телефон абонента: ";
	cin >> sPhoneNumber;
	if (!IsValidNumber(sPhoneNumber))
	{
		return false;
	}
	phoneNumber = sPhoneNumber;

	string sEmail;
	cout << "Электронная почта абонента: ";
	cin >> sEmail;
	email = sEmail;

	return true;
}

void PrintEditActions()
{
	cout << "Выберите действие:" << endl;
	cout << "1. Отредактировать абонента" << endl;
	cout << "2. Удалить абонента" << endl;
	cout << "R. Назад" << endl;
}

void PrintMainActions()
{
	cout << "Выберите действие:" << endl;
	cout << "1. Поиск абонента" << endl;
	cout << "2. Добавить абонента" << endl;
	cout << "3. Отредактировать/удалить абонента" << endl;
	cout << "Q. Выйти" << endl;
}

void EditActions(CSubscriberCollection &collection)
{
	char c = '`';
	PrintEditActions();
	while ((c = cin.get()) != 'R' && c != EOF)
	{
		if (c == '\n')
		{
			continue;
		}
		
		string name, address;
		string phoneNumber = "", email = "";

		cout << "Индекс элемента: ";
		size_t index;
		cin >> index;

		switch (c)
		{
		case '1':
			if (GetSubData(name, address, phoneNumber, email))
			{
				CSubscriber sub(name, address, phoneNumber, email);
				if (!collection.ChangeSubInfo(index, sub))
				{
					cout << "Невозможно изменить абонента!" << endl;
				}
			}
			break;
		case '2':
			if (!collection.DeleteSub(index))
			{
				cout << "Невозможно удалить абонента!" << endl;
			}
			break;
		default:
			break;
		}
		PrintEditActions();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	CAddressBook book;
	ifstream fin(DATABASE_NAME);
 	book.LoadSubCollection(fin);
	fin.close();

	CSubscriberCollection collection = book.GetSubCollection();

	char c = '`';
	PrintMainActions();
	while ((c = cin.get()) != 'Q' && c != EOF)
	{
		if (c == '\n')
		{
			continue;
		}
		string name, address;
		string phoneNumber = "", email = "";

		switch (c)
		{
			case '1':
				if (GetSubData(name, address, phoneNumber, email))
				{
					CSubscriber sub(name, address, phoneNumber, email);
					auto searchRes = collection.FindSub(sub);
					if (searchRes.size() == 0)
					{
						cout << "Нет совпадений!" << endl;
					}
					else
					{
						for (size_t i = 0; i < searchRes.size(); ++i)
						{
							cout <<  i + 1 << collection.GetSub(searchRes[i]).GetName().GetFullName() << endl;
						}
						EditActions(collection);
					}
				}
				break;
			case '2':
				if (GetSubData(name, address,phoneNumber, email))
				{
					CSubscriber sub(name, address, phoneNumber, email);
					if (!collection.AddSub(sub))
					{
						cout << "Невозможно добавить абонента!" << endl;
					}
				}
				break;
			default:
				break;
		}
		PrintMainActions();
	}
	book.SetSubCollection(collection);

	ofstream fout(DATABASE_NAME);
	book.SaveSubCollecton(fout);

	return 0;
}

