#pragma once
class CMulticasedString
{
public:
	CMulticasedString();
	CMulticasedString(const std::string &str);
	~CMulticasedString();

	bool operator<(const CMulticasedString &r) const;
	bool operator==(const CMulticasedString &r) const;

	std::string GetString() const;
	bool IsEqual(const CMulticasedString &str) const;
	bool IsEqual(const std::string &str) const;

	void SetString(const std::string &str);

private:
	std::string m_normalString;
	std::string m_upperString;
};

