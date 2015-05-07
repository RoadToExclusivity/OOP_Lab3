#pragma once
#include "Address.h"
#include "Name.h"
#include "MulticasedString.h"

class CSubscriber
{
public:
	CSubscriber(const std::string &name, 
				const std::string &address = "",
				const std::string &phone = "",
				const std::string &email = "");
	~CSubscriber();

	CSubscriber& operator=(const CSubscriber &sub);

	CName GetName() const;
	CAddress GetAddress() const;
	std::vector<CMulticasedString> GetPhoneNumbers() const;
	std::vector<CMulticasedString> GetEmails() const;

	void SetName(const CName &name);
	void SetAddress(const CAddress &address);
	void AddPhoneNumber(const CMulticasedString &phoneNumber);
	void AddEmail(const CMulticasedString &email);
	void ChangePhoneNumber(size_t index, const std::string &phoneNumber);
	void ChangeEmail(size_t index, const std::string &email);
	void DeletePhoneNumber(size_t index);
	void DeleteEmail(size_t index);
private:
	CName m_name;
	CAddress m_address;
	std::vector<CMulticasedString> m_phoneNumbers;
	std::vector<CMulticasedString> m_emails;
};

