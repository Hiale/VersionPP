#pragma once

#include "Version.h"

class Transformer
{
public:
	virtual ~Transformer();
	virtual std::string getIdentifier() const = 0;
	virtual bool Transform(Version& version, const Version& currentVersion) = 0;
protected:
	bool replaceIdentifier(VersionPart& versionPart, const std::string& replacement);
private:
	bool replace(std::string& str, const std::string& from, const std::string& to);
};

