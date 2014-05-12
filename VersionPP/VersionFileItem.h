#pragma once

#include <memory>
#include "Version.h"

class VersionFileItem 
{
public:
	VersionFileItem(std::string& versionValue, unsigned int line);
private:

	//std::shared_ptr<Version> version;	
	std::string versionValue;
	unsigned int line;

	/*VersionFileItem(std::shared_ptr<Version> version, unsigned int line) : version(version), line(line)
	{
	}*/
};