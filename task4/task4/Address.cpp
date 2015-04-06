#include "stdafx.h"
#include "Address.h"

using namespace std;

CAddress::CAddress(const string &address)
{
	m_fullAddress = address;

	stringstream ss(RemoveExtraSpaces(address));
	string curField;
	size_t i = 0;
	while (getline(ss, curField, ',') && (i < 4))
	{
		CMulticasedString s(RemoveExtraSpaces(curField));
		m_fields[i++] = s;
	}
}

CAddress::~CAddress()
{
}

bool CAddress::IsEqualAddress(const CAddress &address) const
{
	bool res = true;
	for (size_t i = 0; i < 4 && res; ++i)
	{
		string &curStrRef = m_fields[i].GetString(), &addrStrRef = address.m_fields[i].GetString();
		if (curStrRef != "" && addrStrRef != "" && curStrRef != addrStrRef)
		{
			res = false;
		}
	}

	return res;
}

std::string CAddress::GetFullAddress() const
{
	return m_fullAddress;
}