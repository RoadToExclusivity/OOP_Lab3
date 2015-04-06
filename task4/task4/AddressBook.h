#pragma once
#include "SubscriberCollection.h"

class CAddressBook
{
public:
	CAddressBook();
	~CAddressBook();

	CSubscriberCollection GetSubCollection() const;
	
	void SetSubCollection(const CSubscriberCollection &subCollection);
	bool LoadSubCollection(std::ifstream &fin);
	void SaveSubCollecton(std::ofstream &fout);
private:
	CSubscriberCollection m_collection;
};

