#pragma once
#include <memory>
#include <string>
#include <vector>
#include <sstream> 
#include "VersionPart.h"

class Version
{
public:
	Version();
	Version(const std::string& str);
	Version(const unsigned int major, const unsigned int minor, const unsigned int build, const unsigned int revision);
	Version(const unsigned int major, const unsigned int minor, const unsigned int build);
	Version(const unsigned int major, const unsigned int minor);
	Version(const unsigned int major);
	virtual ~Version();
	std::string ToString() const;
	VersionPart& getMajor() const;
	void setMajor(const VersionPart& value);
	VersionPart& getMinor() const;
	void setMinor(const VersionPart& value);
	VersionPart& getBuild() const;
	void setBuild(const VersionPart& value);
	VersionPart& getRevision() const;
	void setRevision(const VersionPart& value);
	bool containsIdentifier(const std::string& identifier) const;
private:
	void parse(const std::string& str);
	static void split(const std::string& input, char delimiter, std::vector<std::string>& elements);
	bool isFinished();
	std::shared_ptr<VersionPart> major;
	std::shared_ptr<VersionPart> minor;
	std::shared_ptr<VersionPart> build;
	std::shared_ptr<VersionPart> revision;
	std::string delimiter;
};

