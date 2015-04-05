#include "stdafx.h"
#include "SubscriberCollection.h"

using namespace std;

bool VectorIntersect(const vector<CMulticasedString> &first, const vector<CMulticasedString> &second)
{
	if (first.size() == 0 || second.size() == 0)
	{
		return true;
	}

	bool res = false;
	for (const auto &elem : first)
	{
		if (find(second.cbegin(), second.cend(), elem) != second.cend())
		{
			res = true;
			break;
		}
	}

	return res;
}

CSubscriberCollection::CSubscriberCollection()
	:m_subs()
{
}

CSubscriberCollection::CSubscriberCollection(const CSubscriber &sub)
	:m_subs()
{
	m_subs.push_back(sub);
}


CSubscriberCollection::~CSubscriberCollection()
{
}

vector<size_t> CSubscriberCollection::FindSub(const CSubscriber &searchSub) const
{
	vector<size_t> res;
	for (size_t i = 0; i < m_subs.size(); ++i)
	{
		const CSubscriber &curSub = m_subs.at(i);
		if (curSub.GetName().IsEqualName(searchSub.GetName()) &&
			curSub.GetAddress().IsEqualAddress(searchSub.GetAddress()) && 
			VectorIntersect(curSub.GetPhoneNumbers(), searchSub.GetPhoneNumbers()) &&
			VectorIntersect(curSub.GetEmails(), searchSub.GetEmails()))
		{
			res.push_back(i);
		}
	}

	return res;
}

bool CSubscriberCollection::AddSub(const CSubscriber &sub)
{
	bool res = true;
	for (const auto &curSub : m_subs)
	{
		for (const auto &curEmail : curSub.GetEmails())
		{
			const auto &newSubEmails = sub.GetEmails();
			if (find(newSubEmails.cbegin(), newSubEmails.cend(), curEmail) != newSubEmails.cend())
			{
				res = false;
				break;
			}
		}

		if (!res)
		{
			break;
		}
	}

	return res;
}

void CSubscriberCollection::ChangeSubInfo(size_t index, const CSubscriber &sub)
{
	m_subs[index] = sub;
}

void CSubscriberCollection::DeleteSub(size_t index)
{
	m_subs.erase(m_subs.begin() + index);
}