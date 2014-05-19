#pragma once

#include "Transformer.h"

class IncrementTransformer : public Transformer
{
public:
	IncrementTransformer();
	virtual ~IncrementTransformer();
	virtual std::string getIdentifier() const = 0;
	virtual bool Transform(Version& version, const Version& currentVersion);
private:
	inline virtual void processPart(VersionPart& newPart, VersionPart& currentPart, VersionPart& priorPart, VersionPart& currentPriorPart) = 0;
};

