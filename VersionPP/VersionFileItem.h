#pragma once

#include <memory>
#include "Version.h"

class VersionFileItem 
{
public:
	VersionFileItem(std::string& versionValue, unsigned int lineNumber);
	VersionFileItem(std::string& versionValue, unsigned int lineNumber, bool createVersion);
	Version& getVersion() const;
	std::string getReplacementValue() const;
	void setReplacementValue(std::string& value);
private:
	std::string versionValue;
	std::string replacementValue;
	unsigned int lineNumber;
	std::unique_ptr<Version> version;
};