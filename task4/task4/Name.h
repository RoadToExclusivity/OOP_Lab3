#pragma once
#include "MulticasedString.h"
#include "RemoveSpaces.h"

class CName
{
public:
	CName(const std::string &name);
	~CName();

	bool IsEqualName(const CName &name) const;
	bool IsEqualName(const std::string &name) const;
	std::string GetFullName() const;

private:
	std::string m_fullName;
	std::set<CMulticasedString> m_nameFields;
};

