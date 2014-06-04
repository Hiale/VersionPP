#include "stdafx.h"
#include "IncrementAlwaysTransformer.h"

IncrementAlwaysTransformer::IncrementAlwaysTransformer()
{

}

IncrementAlwaysTransformer::~IncrementAlwaysTransformer()
{

}

std::string IncrementAlwaysTransformer::getName() const
{
	return "Increment always";
}

std::string IncrementAlwaysTransformer::getIdentifier() const
{
	return "^";
}

bool IncrementAlwaysTransformer::Transform(Version& version, const Version& currentVersion)
{
	processPart(version.getMajor(), currentVersion.getMajor());
	processPart(version.getMinor(), currentVersion.getMinor());
	processPart(version.getBuild(), currentVersion.getBuild());
	processPart(version.getRevision(), currentVersion.getRevision());
	return true;
}

void IncrementAlwaysTransformer::processPart(VersionPart& newPart, VersionPart& currentPart)
{
	if (identifierFound(newPart))
		replaceIdentifier(newPart, std::to_string(currentPart.getIntegerValue() + 1));
}