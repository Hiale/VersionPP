#include "stdafx.h"
#include "Version.h"
#include "VersionPP.h"

Version::Version(const std::string& str)
{
	parse(str);
}

Version::Version(const unsigned int major, const unsigned int minor, const unsigned int build, const unsigned int revision)
{
	setMajor(std::make_shared<VersionPart>(VersionPart(major)));
	setMinor(std::make_shared<VersionPart>(VersionPart(minor)));
	setBuild(std::make_shared<VersionPart>(VersionPart(build)));
	setRevision(std::make_shared<VersionPart>(VersionPart(revision)));
}

Version::Version(const unsigned int major, const unsigned int minor, const unsigned int build) : Version(major, minor, build, 0) {}

Version::Version(const unsigned int major, const unsigned int minor) : Version(major, minor, 0) {}

Version::Version(const unsigned int major) : Version(major, 0) { }

Version::Version() : Version(0) { }

Version::~Version()
{
}

std::shared_ptr<VersionPart> Version::getMajor() const
{
	return major;
}

void Version::setMajor(std::shared_ptr<VersionPart> value)
{
	major = value;
}

std::shared_ptr<VersionPart> Version::getMinor() const
{
	return minor;
}

void Version::setMinor(std::shared_ptr<VersionPart> value)
{
	minor = value;
}

std::shared_ptr<VersionPart> Version::getBuild() const
{
	return build;
}

void Version::setBuild(std::shared_ptr<VersionPart> value)
{
	build = value;
}

std::shared_ptr<VersionPart> Version::getRevision() const
{
	return revision;
}

void Version::setRevision(std::shared_ptr<VersionPart> value)
{
	revision = value;
}

void Version::parse(const std::string& str)
{
	std::vector<std::string> elements;
	split(str, '.', elements);

	while (elements.size() < 4)
		elements.push_back("0");
	setMajor(std::make_shared<VersionPart>(elements.at(0)));
	setMinor(std::make_shared<VersionPart>(elements.at(1)));
	setBuild(std::make_shared<VersionPart>(elements.at(2)));
	setRevision(std::make_shared<VersionPart>(elements.at(3)));

	while (!isFinished()) {
		if (!transformerManager->Transform(*this))
			break;
	}
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
