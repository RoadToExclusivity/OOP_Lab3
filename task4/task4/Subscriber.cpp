#include "stdafx.h"
#include "Subscriber.h"

using namespace std;

CSubscriber::CSubscriber(const string &name,
						 const string &address,
						 const string &phone,
						 const string &email)
						 :m_name(name), m_address(address),
						 m_phoneNumbers(), m_emails()
{
	if (phone != "")
	{
		m_phoneNumbers.push_back(phone);
	}
	if (email != "")
	{
		m_emails.push_back(email);
	}
}


CSubscriber::~CSubscriber()
{
}

CSubscriber& CSubscriber::operator=(const CSubscriber &sub)
{
	if (this == &sub)
	{
		return *this;
	}

	m_name = sub.m_name;
	m_address = sub.m_address;

	m_phoneNumbers.resize(sub.m_phoneNumbers.size());
	if (sub.m_phoneNumbers.size() > 0)
	{
		copy(sub.m_phoneNumbers.cbegin(), sub.m_phoneNumbers.cend(), m_phoneNumbers.begin());
	}
	
	m_emails.resize(sub.m_emails.size()); 
	if (sub.m_emails.size() > 0)
	{
		copy(sub.m_emails.cbegin(), sub.m_emails.cend(), m_emails.begin());
	}

	return *this;
}

CName CSubscriber::GetName() const
{
	return m_name;
}

CAddress CSubscriber::GetAddress() const
{
	return m_address;
}

std::vector<CMulticasedString> CSubscriber::GetPhoneNumbers() const
{
	return m_phoneNumbers;
}

std::vector<CMulticasedString> CSubscriber::GetEmails() const
{
	return m_emails;
}

void CSubscriber::SetName(const CName &name)
{
	if (name.GetFullName() != "")
	{
		m_name = name;
	}
}

void CSubscriber::SetAddress(const CAddress &address)
{
	m_address = address;
}

void CSubscriber::AddPhoneNumber(const CMulticasedString &phoneNumber)
{
	if (phoneNumber.GetString() != "")
	{
		if (m_phoneNumbers.size() == 0 || find(m_phoneNumbers.cbegin(), m_phoneNumbers.cend(), phoneNumber) == m_phoneNumbers.cend())
		{
			m_phoneNumbers.push_back(phoneNumber);
		}
	}
}

void CSubscriber::AddEmail(const CMulticasedString &email)
{
	if (email.GetString() != "")
	{
		if (m_emails.size() == 0 || find(m_emails.cbegin(), m_emails.cend(), email) == m_emails.cend())
		{
			m_emails.push_back(email);
		}
	}
}

void CSubscriber::ChangePhoneNumber(size_t index, const string &phoneNumber)
{
	m_phoneNumbers[index] = phoneNumber;
}

void CSubscriber::ChangeEmail(size_t index, const string &email)
{
	m_emails[index] = email;
}

void CSubscriber::DeletePhoneNumber(size_t index)
{
	if (m_phoneNumbers.size() > 0)
	{
		m_phoneNumbers.erase(m_phoneNumbers.begin() + index);
	}
}

void CSubscriber::DeleteEmail(size_t index)
{
	if (m_emails.size() > 0)
	{
		m_emails.erase(m_emails.begin() + index);
	}
}