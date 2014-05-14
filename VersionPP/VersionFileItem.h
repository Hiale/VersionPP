#pragma once

#include <memory>
#include "Version.h"

class VersionFileItem 
{
public:
	VersionFileItem(std::string& versionValue, unsigned int line);
	Version& getVersion() const;
private:
	std::string versionValue;
	unsigned int line;
	std::unique_ptr<Version> version;
};