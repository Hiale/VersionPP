#include "stdafx.h"
#include "Transformer.h"


Transformer::~Transformer()
{
}

bool Transformer::identifierFound(VersionPart& versionPart)
{
	size_t start_pos = versionPart.getStringValue().find(getIdentifier());
	if (start_pos == std::string::npos)
		return false;
	return true;
}

bool Transformer::replace(std::string& str, const std::string& from, const std::string& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

bool Transformer::replaceIdentifier(VersionPart& versionPart, const std::string& replacement)
{
	std::string str = versionPart.getStringValue();
	bool replaced = replace(str, getIdentifier(), replacement);
	if (replaced)
		versionPart.setStringValue(str);
	return replaced;
}