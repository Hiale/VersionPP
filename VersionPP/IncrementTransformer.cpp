#include "stdafx.h"
#include "IncrementTransformer.h"


IncrementTransformer::IncrementTransformer()
{
}


IncrementTransformer::~IncrementTransformer()
{
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