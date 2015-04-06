#pragma once
#include "MulticasedString.h"
#include "RemoveSpaces.h"

class CAddress
{
public:
	CAddress(const std::string &address);
	~CAddress();

	bool IsEqualAddress(const CAddress &address) const;
	std::string GetFullAddress() const;

private:
	std::string m_fullAddress;
	CMulticasedString m_fields[4];
};

