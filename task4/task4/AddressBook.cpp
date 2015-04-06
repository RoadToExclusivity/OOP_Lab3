#include "stdafx.h"
#include "AddressBook.h"

using namespace std;

CAddressBook::CAddressBook()
	:m_collection()
{
}


CAddressBook::~CAddressBook()
{
}

string ReadString(ifstream &fin)
{
	size_t strLen;
	fin >> strLen;
	fin.get();
	char *strField = new char[strLen + 1];

	fin.read(strField, strLen);
	strField[strLen] = 0;
	string res(strField);
	delete[] strField;
	
	return res;
}

void WriteString(ofstream &fout, const string &str)
{
	fout << str.length() << " ";
	fout << str << " ";
}

CSubscriberCollection CAddressBook::GetSubCollection() const
{
	return m_collection;
}


void CAddressBook::SetSubCollection(const CSubscriberCollection &subCollection)
{
	m_collection = subCollection;
}

bool CAddressBook::LoadSubCollection(ifstream &fin)
{
	size_t subCount;
	if (!(fin >> subCount))
	{
		return false;
	}

	for (size_t i = 0; i < subCount; ++i)
	{
		string name(ReadString(fin));
		string address(ReadString(fin));
		CSubscriber sub(name, address);

		size_t phoneNumbersCount, emailsCount;

		fin >> phoneNumbersCount;
		for (size_t j = 0; j < phoneNumbersCount; j++)
		{
			sub.AddPhoneNumber(CMulticasedString(ReadString(fin)));
		}

		fin >> emailsCount;
		for (size_t j = 0; j < emailsCount; j++)
		{
			sub.AddEmail(CMulticasedString(ReadString(fin)));
		}

		m_collection.AddSub(sub);
	}

	return true;
}

void CAddressBook::SaveSubCollecton(ofstream &fout)
{
	size_t size = m_collection.GetSize();
	fout << size << " ";
	for (size_t i = 0; i < size; ++i)
	{
		WriteString(fout, m_collection.GetSub(i).GetName().GetFullName());
		WriteString(fout, m_collection.GetSub(i).GetAddress().GetFullAddress());
		
		auto phoneNumbers = m_collection.GetSub(i).GetPhoneNumbers();
		auto emails = m_collection.GetSub(i).GetEmails();

		fout << phoneNumbers.size() << " ";
		for (size_t j = 0; j < phoneNumbers.size(); ++j)
		{
			WriteString(fout, phoneNumbers[j].GetString());
		}

		fout << emails.size() << " ";
		for (size_t j = 0; j < emails.size(); ++j)
		{
			WriteString(fout, emails[j].GetString());
		}
	}
}