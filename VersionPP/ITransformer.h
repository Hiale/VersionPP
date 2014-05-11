#pragma once

#include <string>
#include "Version.h"

class ITransformer
{
public :
	virtual ~ITransformer() {}
	virtual std::string getIdentifier() const = 0;
	virtual bool Transform(Version& version) = 0;
};