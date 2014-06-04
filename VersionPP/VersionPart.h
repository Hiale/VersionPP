#pragma once

#include <string>

class VersionPart
{
public:
	VersionPart();
	VersionPart(const std::string& value);
	VersionPart(const unsigned int value);
	virtual ~VersionPart();
	bool hasIntegerValue() const;
	unsigned int getIntegerValue() const;	
	std::string getStringValue() const;
	void setStringValue(const std::string& value);	
private:
	void setIntegerValue(const unsigned int value);
	static bool isNumber(const std::string& str);
	static unsigned int getNumber(const std::string& str);
	unsigned int intValue;
	std::string stringValue;
	bool hasIntValue;
};

