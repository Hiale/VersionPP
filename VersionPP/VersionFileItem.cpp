#include "stdafx.h"
#include "VersionFileItem.h"

VersionFileItem::VersionFileItem(std::string& versionValue, unsigned int line) : versionValue(versionValue), line(line)
{
	version = std::unique_ptr<Version>(new Version(versionValue));
}

Version& VersionFileItem::getVersion() const
{
	return *version;
}

