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
	copy(sub.m_phoneNumbers.cbegin(), sub.m_phoneNumbers.cend(), m_phoneNumbers.begin());
	copy(sub.m_emails.cbegin(), sub.m_emails.cend(), m_emails.begin());

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
	if (name.GetName() != "")
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
		if (find(m_phoneNumbers.cbegin(), m_phoneNumbers.cend(), phoneNumber) != m_phoneNumbers.cend())
		{
			m_phoneNumbers.push_back(phoneNumber);
		}
	}
}

void CSubscriber::AddEmail(const CMulticasedString &email)
{
	if (email.GetString() != "")
	{
		if (find(m_emails.cbegin(), m_emails.cend(), email) != m_emails.cend())
		{
			m_emails.push_back(email);
		}
	}
}