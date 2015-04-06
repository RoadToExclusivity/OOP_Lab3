#include "stdafx.h"
#include "AddressBook.h"


CAddressBook::CAddressBook()
{
}


CAddressBook::~CAddressBook()
{
}

void CAddressBook::GetSubCollection(CSubscriberCollection &subCollection) const
{
	subCollection = m_collection;
}


void CAddressBook::SetSubCollection(const CSubscriberCollection &subCollection)
{
	m_collection = subCollection;
}

bool CAddressBook::LoadSubCollection(CCustomFile &file)
{
	if (!file.IsOpened())
	{
		return false;
	}

	file.Read(&m_collection, sizeof(CSubscriberCollection), 1);
	return true;
}

void CAddressBook::SaveSubCollecton(CCustomFile &file)
{
	file.Write(&m_collection, sizeof(m_collection), 1);
}