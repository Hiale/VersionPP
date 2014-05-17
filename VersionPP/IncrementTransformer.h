#pragma once

#include "Transformer.h"

class IncrementTransformer : public Transformer
{
public:
	IncrementTransformer();
	~IncrementTransformer();
	virtual std::string getIdentifier() const;
	virtual bool Transform(Version& version, const Version& currentVersion);

	void processPart(VersionPart& newPart, VersionPart& currentPart, VersionPart& priorPart, VersionPart& currentPriorPart);
};

