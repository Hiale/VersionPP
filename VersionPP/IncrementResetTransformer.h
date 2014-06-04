#pragma once

#include "Transformer.h"

class IncrementResetTransformer : public Transformer
{
public:
	IncrementResetTransformer();
	virtual ~IncrementResetTransformer();
	virtual std::string getName() const;
	virtual std::string getIdentifier() const;
	virtual bool Transform(Version& version, const Version& currentVersion);
};

