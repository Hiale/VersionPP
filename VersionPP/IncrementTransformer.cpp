#include "stdafx.h"
#include "IncrementTransformer.h"


IncrementTransformer::IncrementTransformer()
{
}

IncrementTransformer::~IncrementTransformer()
{
}

std::string IncrementTransformer::getIdentifier() const
{
	return "+";
}

bool IncrementTransformer::Transform(Version& version, const Version& currentVersion)
{
	VersionPart& newPart = version.getMajor();
	if (identifierFound(newPart))
		replaceIdentifier(newPart, std::to_string(currentVersion.getMajor().getFinalValue() + 1));
	processPart(version.getMinor(), currentVersion.getMinor(), version.getMajor(), currentVersion.getMajor());
	processPart(version.getBuild(), currentVersion.getBuild(), version.getMinor(), currentVersion.getMinor());
	processPart(version.getRevision(), currentVersion.getRevision(), version.getBuild(), currentVersion.getBuild());
	return true;
}

void IncrementTransformer::processPart(VersionPart& newPart, VersionPart& currentPart, VersionPart& priorPart, VersionPart& currentPriorPart)
{
	if (identifierFound(newPart) && priorPart.isFinal() && priorPart.getFinalValue() == currentPriorPart.getFinalValue())
		replaceIdentifier(newPart, std::to_string(currentPart.getFinalValue() + 1));
	else
		replaceIdentifier(newPart, std::to_string(0));
}