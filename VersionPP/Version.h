#pragma once

#include <string>
#include <vector>

class Version
{
public:
	Version();
	Version(const unsigned int major, const unsigned int minor, const unsigned int build, const unsigned int revision);
	Version(const unsigned int major, const unsigned int minor, const unsigned int build);
	Version(const unsigned int major, const unsigned int minor);
	Version(const unsigned int major);
	Version(const std::string& value);
	~Version();
	unsigned int major;
	unsigned int getMajor() const;
	void setMajor(const unsigned int value);
	unsigned int minor;
	unsigned int getMinor() const;
	void setMinor(const unsigned int value);
	unsigned int build;
	unsigned int getBuild() const;
	void setBuild(const unsigned int value);
	unsigned int revision;
	unsigned int getRevision() const;
	void setRevision(const unsigned int value);
private:
	void parse(const std::string& value);
	void split(const std::string& input, char delimiter, std::vector<std::string>& elements);
	unsigned int getNumber(const std::string str);
};

