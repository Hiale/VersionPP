#pragma once

#include <memory>
#include "Version.h"

class VersionFileItem 
{
public:
	VersionFileItem(std::string& versionValue, unsigned int lineNumber, unsigned int linePosition);
	VersionFileItem(std::string& versionValue, unsigned int lineNumber, unsigned int linePosition, bool createVersion);
	Version& getVersion() const;
	std::string getOriginalValue() const;
	unsigned int getLineNumber() const;
	unsigned int getLinePosition() const;
	std::string getReplacementValue() const;
	void setReplacementValue(std::string& value);
private:
	std::string versionValue;
	std::string replacementValue;
	unsigned int lineNumber;
	unsigned int linePosition;
	std::unique_ptr<Version> version;
};