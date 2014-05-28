#include "stdafx.h"
#include "VersionFileItem.h"

VersionFileItem::VersionFileItem(std::string& versionValue, unsigned int versionValueLength, unsigned int lineNumber, unsigned int linePosition) : VersionFileItem(versionValue, versionValueLength, lineNumber, linePosition, true)
{	
}

VersionFileItem::VersionFileItem(std::string& versionValue, unsigned int versionValueLength, unsigned int lineNumber, unsigned int linePosition, bool createVersion) : versionValue(versionValue), versionValueLength(versionValueLength), lineNumber(lineNumber), linePosition(linePosition)
{
	if (createVersion)
		version = std::unique_ptr<Version>(new Version(versionValue));
}

Version& VersionFileItem::getVersion() const
{
	return *version;
}

std::string VersionFileItem::getReplacementValue() const
{
	return replacementValue;
}

void VersionFileItem::setReplacementValue(std::string& value)
{
	replacementValue = value;
}

std::string VersionFileItem::getOriginalValue() const
{
	return versionValue;
}

unsigned int VersionFileItem::getLineNumber() const
{
	return lineNumber;
}

unsigned int VersionFileItem::getLinePosition() const
{
	return linePosition;
}

unsigned int VersionFileItem::getOriginalValueLength() const
{
	return versionValueLength;
}

