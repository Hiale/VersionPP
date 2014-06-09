#include "stdafx.h"
#include "Version.h"

Version::Version(const std::string& str)
{
	parse(str);
}

Version::Version(const unsigned int major, const unsigned int minor, const unsigned int build, const unsigned int revision)
{
	setMajor(VersionPart(major));
	setMinor(VersionPart(minor));
	setBuild(VersionPart(build));
	setRevision(VersionPart(revision));
}

Version::Version(const unsigned int major, const unsigned int minor, const unsigned int build)
{
	setMajor(VersionPart(major));
	setMinor(VersionPart(minor));
	setBuild(VersionPart(build));
	setRevision(VersionPart());
}

Version::Version(const unsigned int major, const unsigned int minor) 
{
	setMajor(VersionPart(major));
	setMinor(VersionPart(minor));
	setBuild(VersionPart());
	setRevision(VersionPart());
}

Version::Version(const unsigned int major) : Version(major, 0)
{
	setMajor(VersionPart(major));
	setMinor(VersionPart());
	setBuild(VersionPart());
	setRevision(VersionPart());
}

Version::Version() : Version(1) { }


Version::~Version()
{
}

VersionPart& Version::getMajor() const
{
	return *major;
}

void Version::setMajor(const VersionPart& value)
{
	major = std::unique_ptr<VersionPart>(new VersionPart(value));
}

VersionPart& Version::getMinor() const
{
	return *minor;
}

void Version::setMinor(const VersionPart& value)
{
	minor = std::unique_ptr<VersionPart>(new VersionPart(value));
}

VersionPart& Version::getBuild() const
{
	return *build;
}

void Version::setBuild(const VersionPart& value)
{
	build = std::unique_ptr<VersionPart>(new VersionPart(value));
}

VersionPart& Version::getRevision() const
{
	return *revision;
}

void Version::setRevision(const VersionPart& value)
{
	revision = std::unique_ptr<VersionPart>(new VersionPart(value));
}

void Version::parse(const std::string& str)
{
	std::vector<std::string> elements;
	std::string delimiter;
	if (str.find(".") != std::string::npos)
		delimiter = ".";
	else if (str.find(",") != std::string::npos)
		delimiter = ",";
	if (delimiter != "")
		split(str, delimiter[0], elements);
	else
		elements.push_back(str == "" ? "1" : str);
	setMajor(VersionPart(elements.at(0)));
	if (elements.size() > 1)
		setMinor(VersionPart(elements.at(1)));
	else
		setMinor(VersionPart());
	if (elements.size() > 2)
		setBuild(VersionPart(elements.at(2)));
	else
		setBuild(VersionPart());
	if (elements.size() > 3)
		setRevision(VersionPart(elements.at(3)));
	else
		setRevision(VersionPart());
}

void Version::split(const std::string& input, char delimiter, std::vector<std::string>& elements)
{
	std::stringstream stringStream(input);
	std::string item;
	while (std::getline(stringStream, item, delimiter))
		elements.push_back(item);
}

bool Version::containsIdentifier(const std::string& identifier) const
{
	return	(major && major->getStringValue().find(identifier) != std::string::npos) ||
			(minor && minor->getStringValue().find(identifier) != std::string::npos) ||
			(build && build->getStringValue().find(identifier) != std::string::npos) ||
			(revision && revision->getStringValue().find(identifier) != std::string::npos);
}

std::string Version::ToString(std::string delimiter) const
{
	return major->getStringValue()
		+ (minor->getStringValue() == "" ? "" : delimiter + minor->getStringValue())
		+ (build->getStringValue() == "" ? "" : delimiter + build->getStringValue())
		+ (revision->getStringValue() == "" ? "" : delimiter + revision->getStringValue());
}

std::string Version::ToStrictString(std::string delimiter) const
{
	return std::to_string(major->getIntegerValue()) + delimiter + std::to_string(minor->getIntegerValue()) + delimiter + std::to_string(build->getIntegerValue()) + delimiter + std::to_string(revision->getIntegerValue());
}
