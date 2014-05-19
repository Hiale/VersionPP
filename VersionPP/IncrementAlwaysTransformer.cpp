#include "stdafx.h"
#include "IncrementAlwaysTransformer.h"

IncrementAlwaysTransformer::IncrementAlwaysTransformer()
{

}

IncrementAlwaysTransformer::~IncrementAlwaysTransformer()
{

}

std::string IncrementAlwaysTransformer::getIdentifier() const
{
	return "^";
}

void IncrementAlwaysTransformer::processPart(VersionPart& newPart, VersionPart& currentPart, VersionPart& priorPart, VersionPart& currentPriorPart)
{
	replaceIdentifier(newPart, std::to_string(currentPart.getFinalValue() + 1));
}