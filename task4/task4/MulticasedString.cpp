#include "stdafx.h"
#include "MulticasedString.h"

using namespace std;

string ToUpper(const string &s)
{
	string res = s;
	transform(res.begin(), res.end(), res.begin(), toupper);

	return res;
}

CMulticasedString::CMulticasedString()
	:m_normalString(""), m_upperString("")
{
}

CMulticasedString::CMulticasedString(const string &str)
	:m_normalString(str), 
	 m_upperString(ToUpper(str))
{
}

CMulticasedString::~CMulticasedString()
{
}

bool CMulticasedString::operator<(const CMulticasedString &r) const
{
	return m_normalString < r.GetString();
}

bool CMulticasedString::operator==(const CMulticasedString &r) const
{
	return m_normalString == r.GetString();
}

string CMulticasedString::GetString() const
{
	return m_normalString;
}

bool CMulticasedString::IsEqual(const CMulticasedString &str) const
{
	return m_upperString == str.m_upperString;
}

bool CMulticasedString::IsEqual(const std::string &str) const
{
	return m_upperString == ToUpper(str);
}

void CMulticasedString::SetString(const string &str)
{
	m_normalString = str;
	m_upperString = ToUpper(str);
}