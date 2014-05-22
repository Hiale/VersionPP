#include "stdafx.h"
#include "VersionFileItem.h"

VersionFileItem::VersionFileItem(std::string& versionValue, unsigned int lineNumber, unsigned int linePosition) : VersionFileItem(versionValue, lineNumber, linePosition, true)
{	
}

VersionFileItem::VersionFileItem(std::string& versionValue, unsigned int lineNumber, unsigned int linePosition, bool createVersion) : versionValue(versionValue), lineNumber(lineNumber), linePosition(linePosition)
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
	if (version)
		return version->ToString();
	return replacementValue;
}

void VersionFileItem::setReplacementValue(std::string& value)
{
	replacementValue = value;
}

