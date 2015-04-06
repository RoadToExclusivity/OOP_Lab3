#pragma once
#include "Subscriber.h"

class CSubscriberCollection
{
public:
	CSubscriberCollection();
	CSubscriberCollection(const CSubscriber &sub);
	~CSubscriberCollection();

	size_t GetSize() const;
	CSubscriber GetSub(size_t index) const;
	std::vector<size_t> FindSub(const CSubscriber &sub) const;

	bool AddSub(const CSubscriber &sub);
	bool ChangeSubInfo(size_t index, const CSubscriber &sub);
	bool DeleteSub(size_t index);
private:
	std::vector<CSubscriber> m_subs;
};

