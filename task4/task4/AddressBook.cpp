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

size_t ReadNumber(ifstream &fin)
{
	size_t res = 0;
	fin.read(reinterpret_cast<char*>(&res), sizeof size_t);
	return res;
}

string ReadString(ifstream &fin)
{
	size_t strLen = ReadNumber(fin);
	
	char *strField = new char[strLen + 1];
	fin.read(strField, strLen);
	strField[strLen] = '\0';
	string res(strField);
	delete[] strField;
	
	return res;
}

void WriteString(ofstream &fout, const string &str)
{
	size_t sLen = str.length();
	fout.write(reinterpret_cast<const char*>(&sLen), sizeof sLen);
	fout.write(str.c_str(), sLen);
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
	size_t subCount = ReadNumber(fin);
	for (size_t i = 0; i < subCount; ++i)
	{
		string name(ReadString(fin));
		if (name == "")
		{
			return false;
		}

		string address(ReadString(fin));
		CSubscriber sub(name, address);

		size_t phoneNumbersCount = ReadNumber(fin);
		for (size_t j = 0; j < phoneNumbersCount; j++)
		{
			sub.AddPhoneNumber(CMulticasedString(ReadString(fin)));
		}

		size_t emailsCount = ReadNumber(fin);
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
	fout.write(reinterpret_cast<const char*>(&size), sizeof size);
	for (size_t i = 0; i < size; ++i)
	{
		WriteString(fout, m_collection.GetSub(i).GetName().GetFullName());
		WriteString(fout, m_collection.GetSub(i).GetAddress().GetFullAddress());
		
		auto phoneNumbers = m_collection.GetSub(i).GetPhoneNumbers();
		auto emails = m_collection.GetSub(i).GetEmails();

		size_t phoneNumbersSize = phoneNumbers.size(), emailsSize = emails.size();
		fout.write(reinterpret_cast<const char*>(&phoneNumbersSize), sizeof phoneNumbersSize);
		for (size_t j = 0; j < phoneNumbers.size(); ++j)
		{
			WriteString(fout, phoneNumbers[j].GetString());
		}

		fout.write(reinterpret_cast<const char*>(&emailsSize), sizeof emailsSize);
		for (size_t j = 0; j < emails.size(); ++j)
		{
			WriteString(fout, emails[j].GetString());
		}
	}
}