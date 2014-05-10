#pragma once

#include <string>

class VersionPart
{
public:
	VersionPart(const std::string& value);
	virtual ~VersionPart();
	unsigned int getFinalValue() const;
	void setFinalValue(const unsigned int value);
	std::string getStringValue() const;
	bool isFinal() const;
private:
	static bool isNumber(const std::string& str);
	static unsigned int getNumber(const std::string& str);
	unsigned int finalValue;
	std::string stringValue;
	bool final;
};

