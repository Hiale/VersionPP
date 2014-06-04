#pragma once

#include "Transformer.h"

class IncrementAlwaysTransformer : public Transformer
{
public:
	IncrementAlwaysTransformer();
	virtual ~IncrementAlwaysTransformer();
	virtual std::string getName() const;
	virtual std::string getIdentifier() const;
	virtual bool Transform(Version& version, const Version& currentVersion);
private:
	inline void processPart(VersionPart& newPart, VersionPart& currentPart);
};