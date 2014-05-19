#pragma once

#include "IncrementTransformer.h"

class IncrementResetTransformer : public IncrementTransformer
{
public:
	IncrementResetTransformer();
	virtual ~IncrementResetTransformer();
	virtual std::string getIdentifier() const;
private:
	inline void processPart(VersionPart& newPart, VersionPart& currentPart, VersionPart& priorPart, VersionPart& currentPriorPart);
};

