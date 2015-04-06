#pragma once
#include "Subscriber.h"

class CSubscriberCollection
{
public:
	CSubscriberCollection();
	CSubscriberCollection(const CSubscriber &sub);
	~CSubscriberCollection();

	std::vector<size_t> FindSub(const CSubscriber &sub) const;

	bool AddSub(const CSubscriber &sub);
	void ChangeSubInfo(size_t index, const CSubscriber &sub);
	void DeleteSub(size_t index);
private:
	std::vector<CSubscriber> m_subs;
};

