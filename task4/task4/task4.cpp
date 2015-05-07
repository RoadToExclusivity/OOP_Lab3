#include "stdafx.h"
#include "AddressBook.h"
#include "Address.h"
#include "Name.h"
#include "Subscriber.h"

using namespace std;

const char *DATABASE_NAME = "db.txt";

bool IsValidName(const string &s)
{
	bool res = true;
	for (auto c : s)
	{
		if (!isalpha(c) && c != ' ')
		{
			res = false;
			break;
		}
	}

	return res;
}

bool IsValidNumber(const string &s)
{
	bool res = true;
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

bool ReadName(string &name)
{
	cout << "Имя абонента: ";

	getline(cin, name);
	if (!IsValidName(name) && name != "")
	{
		return false;
	}

	return true;
}

void ReadAddress(string &address)
{
	cout << "Адрес абонента: ";
	getline(cin, address);
}

bool ReadPhoneNumber(string &phoneNumber)
{
	cout << "Мобильный телефон абонента: ";

	getline(cin, phoneNumber);
	if (!IsValidNumber(phoneNumber))
	{
		return false;
	}

	return true;
}

void ReadEmail(string &email)
{
	cout << "Электронная почта абонента: ";
	getline(cin, email);
}

bool ReadIndex(size_t &index, size_t maxIndex)
{
	cout << "Индекс элемента: ";
	string strIndex;
	getline(cin, strIndex);
	if (strIndex == "" || !IsValidNumber(strIndex))
	{
		return false;
	}
	index = stol(strIndex);
	if (index < 1 || index > maxIndex)
	{
		return false;
	}

	return true;
}

bool GetSubData(string &name, string &address, string &phoneNumber, string &email)
{
	if (!ReadName(name))
	{
		cout << "Неверное имя абонента !" << endl << endl;
		return false;
	}

	ReadAddress(address);

	if (!ReadPhoneNumber(phoneNumber))
	{
		cout << "Неверный формат телефона!" << endl << endl;
		return false;
	}

	ReadEmail(email);

	return true;
}

void PrintMulticasedVector(const vector<CMulticasedString> &a)
{
	if (a.size() > 0)
	{
		cout << '\t' << a.size() << endl;
		
		size_t counter = 1;
		for (const auto &elem : a)
		{
			cout << '\t' << counter << ") " << elem.GetString() << endl;
			counter++;
		}
	}
}

void PrintSubCollectionInfo(const CSubscriberCollection &collection, const vector<size_t> &indexes)
{
	for (size_t i = 0; i < indexes.size(); ++i)
	{
		CSubscriber& sub = collection.GetSub(indexes[i]);
		cout << i + 1 << ". " << sub.GetName().GetFullName() << endl;
		cout << '\t' << sub.GetAddress().GetFullAddress() << endl;
		PrintMulticasedVector(sub.GetPhoneNumbers());
		PrintMulticasedVector(sub.GetEmails());
	}
	cout << endl;
}

void PrintEditSubscriberActions()
{
	cout << "Выберите действие:" << endl;
	cout << "1. Отредактировать абонента полностью" << endl;
	cout << "2. Изменить имя абонента" << endl;
	cout << "3. Изменить адрес абонента" << endl;
	cout << "4. Добавить телефон" << endl;
	cout << "5. Добавить e-mail" << endl;
	cout << "6. Изменить телефон" << endl;
	cout << "7. Изменить e-mail" << endl;
	cout << "8. Удалить телефон" << endl;
	cout << "9. Удалить e-mail" << endl;
	cout << "R. Назад" << endl;
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

void EditSubscriberActions(CSubscriberCollection &collection, size_t index)
{
	string choice = "`";
	PrintEditSubscriberActions();
	while (choice != "R")
	{
		getline(cin, choice);
		string name = "", address = "", phoneNumber = "", email = "";
		CSubscriber curSub = collection.GetSub(index);

		if (choice == "1")
		{
			if (GetSubData(name, address, phoneNumber, email))
			{
				CSubscriber newSub(name, address, phoneNumber, email);
				if (!collection.ChangeSubInfo(index, newSub))
				{
					cout << "Невозможно изменить абонента!" << endl;
				}
				else
				{
					cout << "Абонент успешно изменен !" << endl;
				}
			}
			cout << endl;
		}
		else
		{
			if (choice == "2")
			{
				ReadAddress(address);
				curSub.SetAddress(address);
				if (!collection.ChangeSubInfo(index, curSub))
				{
					cout << "Невозможно изменить абонента!" << endl;
				}
				else
				{
					cout << "Адрес успешно изменен !" << endl;
				}
			}
			if (choice == "3")
			{
				if (!ReadName(name))
				{
					cout << "Неверное имя абонента !" << endl;
				}
				else
				{
					curSub.SetName(name);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "Невозможно изменить абонента!" << endl;
					}
					else
					{
						cout << "Имя успешно изменено !" << endl;
					}
				}
			}
			if (choice == "4")
			{
				if (!ReadPhoneNumber(phoneNumber))
				{
					cout << "Неверный номер телефона !" << endl;
				}
				else
				{
					curSub.AddPhoneNumber(phoneNumber);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "Невозможно изменить абонента!" << endl;
					}
					else
					{
						cout << "Номер успешно добавлен !" << endl;
					}
				}
			}
			if (choice == "5")
			{
				ReadEmail(email);
				curSub.AddEmail(email);
				if (!collection.ChangeSubInfo(index, curSub))
				{
					cout << "Невозможно изменить абонента!" << endl;
				}
				else
				{
					cout << "E-mail успешно добавлен !" << endl;
				}
			}
			if (choice == "6")
			{
				PrintMulticasedVector(curSub.GetPhoneNumbers());
				size_t newIndex;
				if (!ReadIndex(newIndex, curSub.GetPhoneNumbers().size() + 1))
				{
					cout << "Неверный индекс" << endl;
				}
				else
				{
					newIndex--;
					if (!ReadPhoneNumber(phoneNumber))
					{
						cout << "Неверный номер телефона !" << endl;
					}
					else
					{
						curSub.ChangePhoneNumber(newIndex, phoneNumber);
						if (!collection.ChangeSubInfo(index, curSub))
						{
							cout << "Невозможно изменить абонента!" << endl;
						}
						else
						{
							cout << "Номер успешно изменен !" << endl;
						}
					}
				}
			}
			if (choice == "7")
			{
				PrintMulticasedVector(curSub.GetEmails());
				size_t newIndex;
				if (!ReadIndex(newIndex, curSub.GetEmails().size() + 1))
				{
					cout << "Неверный индекс" << endl;
				}
				else
				{
					newIndex--;
					ReadEmail(email);
					curSub.ChangePhoneNumber(newIndex, phoneNumber);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "Невозможно изменить абонента!" << endl;
					}
					else
					{
						cout << "E-mail успешно изменен !" << endl;
					}
				}
			}
			if (choice == "8")
			{
				PrintMulticasedVector(curSub.GetPhoneNumbers());
				size_t newIndex;
				if (!ReadIndex(newIndex, curSub.GetPhoneNumbers().size() + 1))
				{
					cout << "Неверный индекс" << endl;
				}
				else
				{
					newIndex--;
					curSub.DeletePhoneNumber(newIndex);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "Невозможно изменить абонента!" << endl;
					}
					else
					{
						cout << "Номер успешно удален !" << endl;
					}
				}
			}
			if (choice == "9")
			{
				PrintMulticasedVector(curSub.GetEmails());
				size_t newIndex;
				if (!ReadIndex(newIndex, curSub.GetEmails().size() + 1))
				{
					cout << "Неверный индекс" << endl;
				}
				else
				{
					newIndex--;
					curSub.DeleteEmail(newIndex);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "Невозможно изменить абонента!" << endl;
					}
					else
					{
						cout << "E-mail успешно удален !" << endl;
					}
				}
			}

			cout << endl;
		}

		PrintEditSubscriberActions();
	}
}

void EditActions(CSubscriberCollection &collection, size_t maxIndex)
{
	string choice = "`";
	PrintEditActions();
	while (choice != "R")
	{
		getline(cin, choice);
		string name = "", address = "", phoneNumber = "", email = "";

		size_t index;

		if (choice != "R" && ReadIndex(index, maxIndex))
		{
			index--;
			if (choice == "1")
			{	
				CSubscriber sub = collection.GetSub(index);
				EditSubscriberActions(collection, index);
			}
			else
			{
				if (choice == "2")
				{
					if (!collection.DeleteSub(index))
					{
						cout << "Невозможно удалить абонента!" << endl;
					}
					else
					{
						cout << "Абонент успешно удален !" << endl;
					}
				}
				cout << endl;
			}
		}
		
		PrintEditActions();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	CAddressBook book;
	ifstream fin(DATABASE_NAME, ios::binary);
	if (fin)
	{
		if (!book.LoadSubCollection(fin))
		{
			string choice = "";
			while (choice != "Y" && choice != "N")
			{
				cout << "Ошибка открытия базы данных!" << endl << "Удалить и создать новую ? (Y/N)" << endl;
				getline(cin, choice);
			}
			if (choice == "N")
			{
				return 0;
			}
		}

		fin.close();
	}
	
	CSubscriberCollection collection = book.GetSubCollection();

	string choice = "";
	PrintMainActions();
	while (choice != "Q")
	{
		getline(cin, choice);
		string name = "", address = "", phoneNumber = "", email = "";

		if (choice == "1")
		{
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
					cout << searchRes.size() << " совпадений: " << endl;
					PrintSubCollectionInfo(collection, searchRes);
				}
			}
			cout << endl;
		}
		else
		{
			if (choice == "2")
			{
				if (GetSubData(name, address, phoneNumber, email))
				{
					CSubscriber sub(name, address, phoneNumber, email);
					if (!collection.AddSub(sub))
					{
						cout << "Невозможно добавить абонента!" << endl;
					}
					else
					{
						cout << "Абонент добавлен!" << endl;
					}
				}
				cout << endl;
			}
			else
			{
				if (choice == "3")
				{
					if (GetSubData(name, address, phoneNumber, email))
					{
						CSubscriber sub(name, address, phoneNumber, email);
						auto searchRes = collection.FindSub(sub);
						if (searchRes.size() == 0)
						{
							cout << "Нет совпадений по данному абоненту!" << endl;
						}
						else
						{
							cout << searchRes.size() << " совпадений: " << endl;
							PrintSubCollectionInfo(collection, searchRes);
							EditActions(collection, searchRes.size() + 1);
						}
					}
					cout << endl;
				}
			}
		}

		PrintMainActions();
	}
	book.SetSubCollection(collection);

	ofstream fout(DATABASE_NAME, ios::binary);
	book.SaveSubCollecton(fout);

	return 0;
}

