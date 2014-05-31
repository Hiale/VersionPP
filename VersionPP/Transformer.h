#pragma once

#include "Version.h"

class Transformer
{
public:
	virtual ~Transformer();
	virtual std::string getName() const = 0;
	virtual std::string getIdentifier() const = 0;	
	virtual bool Transform(Version& version, const Version& currentVersion) = 0;	
protected:
	bool identifierFound(VersionPart& versionPart);
	bool replaceIdentifier(VersionPart& versionPart, const std::string& replacement);
private:
	static bool replace(std::string& str, const std::string& from, const std::string& to);
};

