#include "stdafx.h"
#include "Version.h"
#include "VersionPP.h"

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

Version::Version(const unsigned int major, const unsigned int minor, const unsigned int build) : Version(major, minor, build, 0) {}

Version::Version(const unsigned int major, const unsigned int minor) : Version(major, minor, 0) {}

Version::Version(const unsigned int major) : Version(major, 0) { }

Version::Version() : Version(0) { }

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
	if (str.find(".") != std::string::npos)
		split(str, '.', elements);
	else if (str.find(",") != std::string::npos)
		split(str, ',', elements);
	else
		throw std::exception("Not a valid version format.");

	while (elements.size() < 4)
		elements.push_back("0");
	setMajor(VersionPart(elements.at(0)));
	setMinor(VersionPart(elements.at(1)));
	setBuild(VersionPart(elements.at(2)));
	setRevision(VersionPart(elements.at(3)));

	/*while (!isFinished()) {
		if (!transformerManager->Transform(*this))
			break;
	}*/
}

void Version::split(const std::string& input, char delimiter, std::vector<std::string>& elements)
{
	std::stringstream stringStream(input);
	std::string item;
	while (std::getline(stringStream, item, delimiter))
		elements.push_back(item);
}

bool Version::isFinished()
{
	return major && major->isFinal() && minor && minor->isFinal() && build && build->isFinal() && revision && revision->isFinal();
}

bool Version::containsIdentifier(const std::string& identifier) const
{
	return	(major && major->getStringValue().find(identifier) != std::string::npos) ||
			(minor && minor->getStringValue().find(identifier) != std::string::npos) ||
			(build && build->getStringValue().find(identifier) != std::string::npos) ||
			(revision && revision->getStringValue().find(identifier) != std::string::npos);
}