#include "stdafx.h"
#include "VersionPart.h"
#include <algorithm>
#include <cctype>


VersionPart::VersionPart(const std::string& value)
{
	final = false;
	finalValue = 0;
	setStringValue(value);
}

VersionPart::~VersionPart()
{

}

unsigned int VersionPart::getFinalValue() const
{
	return finalValue;
}

void VersionPart::setFinalValue(const unsigned int value)
{
	finalValue = value;
	final = true;
}

std::string VersionPart::getStringValue() const
{
	return stringValue;
}

void VersionPart::setStringValue(const std::string& value)
{
	stringValue = value;
	if (isNumber(value))
		setFinalValue(getNumber(stringValue));
}

bool VersionPart::isFinal() const
{
	return final;
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