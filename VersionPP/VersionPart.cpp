#include "stdafx.h"
#include "VersionPart.h"
#include <algorithm>
#include <cctype>


VersionPart::VersionPart(const std::string& value) : hasIntValue(false), intValue(0)
{
	setStringValue(value);
}

VersionPart::VersionPart(const unsigned int value)
{
	stringValue = std::to_string(value);
	setIntegerValue(value);
}

VersionPart::VersionPart() : VersionPart("")
{
}

VersionPart::~VersionPart()
{

}

unsigned int VersionPart::getIntegerValue() const
{
	return intValue;
}

void VersionPart::setIntegerValue(const unsigned int value)
{
	intValue = value;
	hasIntValue = true;
}

std::string VersionPart::getStringValue() const
{
	return stringValue;
}

void VersionPart::setStringValue(const std::string& value)
{
	stringValue = value;
	if (isNumber(value))
		setIntegerValue(getNumber(stringValue));
	else
		hasIntValue = false;
}

bool VersionPart::hasIntegerValue() const
{
	return hasIntValue;
}

bool VersionPart::isNumber(const std::string& str)
{
	return !str.empty() && std::find_if(str.begin(), str.end(), [](char c) { return !std::isdigit(c); }) == str.end();
}

unsigned int VersionPart::getNumber(const std::string& str)
{
	try
	{
		return std::stoul(str);
	}
	catch (std::exception& e)
	{
		return 0;
	}
}