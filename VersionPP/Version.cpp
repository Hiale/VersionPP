#include "stdafx.h"
#include "Version.h"
#include <sstream>

Version::Version(const unsigned int major, const unsigned int minor, const unsigned int build, const unsigned int revision)
{
	setMajor(major);
	setMinor(minor);
	setBuild(build);
	setRevision(revision);
}

Version::Version(const unsigned int major, const unsigned int minor, const unsigned int build) : Version(major, minor, build, 0) {}

Version::Version(const unsigned int major, const unsigned int minor) : Version(major, minor, 0) {}

Version::Version(const unsigned int major) : Version(major, 0) {}

Version::Version() : Version(0) {}

Version::Version(const std::string& value)
{
	
}



Version::~Version()
{

}

unsigned int Version::getMajor() const
{
	return major;
}

void Version::setMajor(const unsigned int value)
{
	major = value;
}

unsigned int Version::getMinor() const
{
	return minor;
}

void Version::setMinor(const unsigned int value)
{
	minor = value;
}

unsigned int Version::getBuild() const
{
	return build;
}

void Version::setBuild(const unsigned int value)
{
	build = value;
}

unsigned int Version::getRevision() const
{
	return revision;
}

void Version::setRevision(const unsigned int value)
{
	revision = value;
}

void Version::parse(const std::string& value)
{
	std::vector<std::string> elements;
	split(value, '.', elements);
	if (elements.size() > 0)
	{
		setMajor(getNumber(elements.at(0)));
	}
	if (elements.size() > 1)
	{
		setMajor(getNumber(elements.at(1)));
	}
	if (elements.size() > 2)
	{
		setBuild(getNumber(elements.at(2)));
	}
	if (elements.size() > 3)
	{
		setRevision(getNumber(elements.at(3)));
	}
}

void Version::split(const std::string& input, char delimiter, std::vector<std::string>& elements)
{
	std::stringstream stringStream(input);
	std::string item;
	while (std::getline(stringStream, item, delimiter)) {
		elements.push_back(item);
	}
}

unsigned int Version::getNumber(const std::string str)
{
	try
	{
		return std::stoul(str);
	}
	catch (std::exception& e)
	{
		return 0;
	}
	

}
