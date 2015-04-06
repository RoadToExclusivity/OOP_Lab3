#pragma once
#include "CustomFile.h"
#include "SubscriberCollection.h"

class CAddressBook
{
public:
	CAddressBook();
	~CAddressBook();

	void GetSubCollection(CSubscriberCollection &subCollection) const;
	
	void SetSubCollection(const CSubscriberCollection &subCollection);
	bool LoadSubCollection(CCustomFile &file);
	void SaveSubCollecton(CCustomFile &file);
private:
	CSubscriberCollection m_collection;
};

