#include "stdafx.h"
#include "Name.h"

using namespace std;

CName::CName(const string &name)
{
	m_fullName = name;
	stringstream ss(RemoveExtraSpaces(name));
	string curField;
	while (getline(ss, curField, ' '))
	{
		CMulticasedString s(curField);
		m_nameFields.insert(s);
	}
}

CName::~CName()
{
}

std::string CName::GetFullName() const
{
	return m_fullName;
}

bool CName::IsEqualName(const CName &name) const
{
	bool res = true;
	for (const auto &nameField : name.m_nameFields)
	{
		if (find_if(m_nameFields.cbegin(), m_nameFields.cend(),
			[&nameField](const CMulticasedString &str)
			{
				return str.IsEqual(nameField);
			}) == m_nameFields.cend())
		{
			res = false;
			break;
		}
	}

	return res;
}

bool CName::IsEqualName(const string &name) const
{
	bool res = true;
	stringstream ss(RemoveExtraSpaces(name));
	string curField;
	while (getline(ss, curField, ' '))
	{
		if (find_if(m_nameFields.cbegin(), m_nameFields.cend(), 
			[&curField](const CMulticasedString &str)
			{
				return str.IsEqual(curField);
			}) == m_nameFields.cend())
		{
			res = false;
			break;
		}
	}

	return res;
}