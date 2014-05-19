#pragma once

#include "IncrementTransformer.h"

class IncrementAlwaysTransformer : public IncrementTransformer
{
public:
	IncrementAlwaysTransformer();
	virtual ~IncrementAlwaysTransformer();
	virtual std::string getIdentifier() const;
private:
	inline void processPart(VersionPart& newPart, VersionPart& currentPart, VersionPart& priorPart, VersionPart& currentPriorPart);
};