#include "stdafx.h"
#include "IncrementResetTransformer.h"


IncrementResetTransformer::IncrementResetTransformer()
{
}

IncrementResetTransformer::~IncrementResetTransformer()
{
}

std::string IncrementResetTransformer::getIdentifier() const
{
	return "+";
}

void IncrementResetTransformer::processPart(VersionPart& newPart, VersionPart& currentPart, VersionPart& priorPart, VersionPart& currentPriorPart)
{
	if (identifierFound(newPart) && priorPart.isFinal() && priorPart.getFinalValue() == currentPriorPart.getFinalValue())
		replaceIdentifier(newPart, std::to_string(currentPart.getFinalValue() + 1));
	else
		replaceIdentifier(newPart, std::to_string(0));
}