#include "stdafx.h"
#include "IncrementResetTransformer.h"


IncrementResetTransformer::IncrementResetTransformer()
{
}

IncrementResetTransformer::~IncrementResetTransformer()
{
}

std::string IncrementResetTransformer::getName() const
{
	return "Increment with reset";
}

std::string IncrementResetTransformer::getIdentifier() const
{
	return "+";
}

bool IncrementResetTransformer::Transform(Version& version, const Version& currentVersion)
{
	if (identifierFound(version.getMajor()))
	{
		replaceIdentifier(version.getMajor(), std::to_string(currentVersion.getMajor().getIntegerValue() + 1));
	}

	if (identifierFound(version.getMinor()))
	{
		if (version.getMajor().hasIntegerValue() && version.getMajor().getIntegerValue() == currentVersion.getMajor().getIntegerValue())
			replaceIdentifier(version.getMinor(), std::to_string(currentVersion.getMinor().getIntegerValue() + 1));
		else
			replaceIdentifier(version.getMinor(), std::to_string(0));
	}

	if (identifierFound(version.getBuild()))
	{
		if (version.getMajor().hasIntegerValue() && version.getMajor().getIntegerValue() == currentVersion.getMajor().getIntegerValue() &&
			version.getMinor().hasIntegerValue() && version.getMinor().getIntegerValue() == currentVersion.getMinor().getIntegerValue())
			replaceIdentifier(version.getBuild(), std::to_string(currentVersion.getBuild().getIntegerValue() + 1));
		else
			replaceIdentifier(version.getBuild(), std::to_string(0));
	}

	if (identifierFound(version.getRevision()))
	{
		if (version.getMajor().hasIntegerValue() && version.getMajor().getIntegerValue() == currentVersion.getMajor().getIntegerValue() &&
			version.getMinor().hasIntegerValue() && version.getMinor().getIntegerValue() == currentVersion.getMinor().getIntegerValue() &&
			version.getBuild().hasIntegerValue() && version.getBuild().getIntegerValue() == currentVersion.getBuild().getIntegerValue())
			replaceIdentifier(version.getRevision(), std::to_string(currentVersion.getRevision().getIntegerValue() + 1));
		else
			replaceIdentifier(version.getRevision(), std::to_string(0));
	}	
	return true;
}

