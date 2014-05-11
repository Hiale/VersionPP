#pragma once

#include <string>

class VersionPart
{
public:
	VersionPart(const std::string& value);
	virtual ~VersionPart();
	unsigned int getFinalValue() const;	
	std::string getStringValue() const;
	void setStringValue(const std::string& value);
	bool isFinal() const;
private:
	void setFinalValue(const unsigned int value);
	static bool isNumber(const std::string& str);
	static unsigned int getNumber(const std::string& str);
	unsigned int finalValue;
	std::string stringValue;
	bool final;
};

