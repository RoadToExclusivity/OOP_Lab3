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
	cout << "��� ��������: ";

	getline(cin, name);
	if (!IsValidName(name) && name != "")
	{
		return false;
	}

	return true;
}

void ReadAddress(string &address)
{
	cout << "����� ��������: ";
	getline(cin, address);
}

bool ReadPhoneNumber(string &phoneNumber)
{
	cout << "��������� ������� ��������: ";

	getline(cin, phoneNumber);
	if (!IsValidNumber(phoneNumber))
	{
		return false;
	}

	return true;
}

void ReadEmail(string &email)
{
	cout << "����������� ����� ��������: ";
	getline(cin, email);
}

bool ReadIndex(size_t &index, size_t maxIndex)
{
	cout << "������ ��������: ";
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
		cout << "�������� ��� �������� !" << endl << endl;
		return false;
	}

	ReadAddress(address);

	if (!ReadPhoneNumber(phoneNumber))
	{
		cout << "�������� ������ ��������!" << endl << endl;
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
	cout << "�������� ��������:" << endl;
	cout << "1. ��������������� �������� ���������" << endl;
	cout << "2. �������� ��� ��������" << endl;
	cout << "3. �������� ����� ��������" << endl;
	cout << "4. �������� �������" << endl;
	cout << "5. �������� e-mail" << endl;
	cout << "6. �������� �������" << endl;
	cout << "7. �������� e-mail" << endl;
	cout << "8. ������� �������" << endl;
	cout << "9. ������� e-mail" << endl;
	cout << "R. �����" << endl;
}

void PrintEditActions()
{
	cout << "�������� ��������:" << endl;
	cout << "1. ��������������� ��������" << endl;
	cout << "2. ������� ��������" << endl;
	cout << "R. �����" << endl;
}

void PrintMainActions()
{
	cout << "�������� ��������:" << endl;
	cout << "1. ����� ��������" << endl;
	cout << "2. �������� ��������" << endl;
	cout << "3. ���������������/������� ��������" << endl;
	cout << "Q. �����" << endl;
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
					cout << "���������� �������� ��������!" << endl;
				}
				else
				{
					cout << "������� ������� ������� !" << endl;
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
					cout << "���������� �������� ��������!" << endl;
				}
				else
				{
					cout << "����� ������� ������� !" << endl;
				}
			}
			if (choice == "3")
			{
				if (!ReadName(name))
				{
					cout << "�������� ��� �������� !" << endl;
				}
				else
				{
					curSub.SetName(name);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "���������� �������� ��������!" << endl;
					}
					else
					{
						cout << "��� ������� �������� !" << endl;
					}
				}
			}
			if (choice == "4")
			{
				if (!ReadPhoneNumber(phoneNumber))
				{
					cout << "�������� ����� �������� !" << endl;
				}
				else
				{
					curSub.AddPhoneNumber(phoneNumber);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "���������� �������� ��������!" << endl;
					}
					else
					{
						cout << "����� ������� �������� !" << endl;
					}
				}
			}
			if (choice == "5")
			{
				ReadEmail(email);
				curSub.AddEmail(email);
				if (!collection.ChangeSubInfo(index, curSub))
				{
					cout << "���������� �������� ��������!" << endl;
				}
				else
				{
					cout << "E-mail ������� �������� !" << endl;
				}
			}
			if (choice == "6")
			{
				PrintMulticasedVector(curSub.GetPhoneNumbers());
				size_t newIndex;
				if (!ReadIndex(newIndex, curSub.GetPhoneNumbers().size() + 1))
				{
					cout << "�������� ������" << endl;
				}
				else
				{
					newIndex--;
					if (!ReadPhoneNumber(phoneNumber))
					{
						cout << "�������� ����� �������� !" << endl;
					}
					else
					{
						curSub.ChangePhoneNumber(newIndex, phoneNumber);
						if (!collection.ChangeSubInfo(index, curSub))
						{
							cout << "���������� �������� ��������!" << endl;
						}
						else
						{
							cout << "����� ������� ������� !" << endl;
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
					cout << "�������� ������" << endl;
				}
				else
				{
					newIndex--;
					ReadEmail(email);
					curSub.ChangePhoneNumber(newIndex, phoneNumber);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "���������� �������� ��������!" << endl;
					}
					else
					{
						cout << "E-mail ������� ������� !" << endl;
					}
				}
			}
			if (choice == "8")
			{
				PrintMulticasedVector(curSub.GetPhoneNumbers());
				size_t newIndex;
				if (!ReadIndex(newIndex, curSub.GetPhoneNumbers().size() + 1))
				{
					cout << "�������� ������" << endl;
				}
				else
				{
					newIndex--;
					curSub.DeletePhoneNumber(newIndex);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "���������� �������� ��������!" << endl;
					}
					else
					{
						cout << "����� ������� ������ !" << endl;
					}
				}
			}
			if (choice == "9")
			{
				PrintMulticasedVector(curSub.GetEmails());
				size_t newIndex;
				if (!ReadIndex(newIndex, curSub.GetEmails().size() + 1))
				{
					cout << "�������� ������" << endl;
				}
				else
				{
					newIndex--;
					curSub.DeleteEmail(newIndex);
					if (!collection.ChangeSubInfo(index, curSub))
					{
						cout << "���������� �������� ��������!" << endl;
					}
					else
					{
						cout << "E-mail ������� ������ !" << endl;
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
						cout << "���������� ������� ��������!" << endl;
					}
					else
					{
						cout << "������� ������� ������ !" << endl;
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
				cout << "������ �������� ���� ������!" << endl << "������� � ������� ����� ? (Y/N)" << endl;
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
					cout << "��� ����������!" << endl;
				}
				else
				{
					cout << searchRes.size() << " ����������: " << endl;
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
						cout << "���������� �������� ��������!" << endl;
					}
					else
					{
						cout << "������� ��������!" << endl;
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
							cout << "��� ���������� �� ������� ��������!" << endl;
						}
						else
						{
							cout << searchRes.size() << " ����������: " << endl;
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

