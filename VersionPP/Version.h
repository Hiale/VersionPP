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
	std::shared_ptr<VersionPart> getMajor() const;
	void setMajor(std::shared_ptr<VersionPart> value);
	std::shared_ptr<VersionPart> getMinor() const;
	void setMinor(std::shared_ptr<VersionPart> value);
	std::shared_ptr<VersionPart> getBuild() const;
	void setBuild(std::shared_ptr<VersionPart> value);
	std::shared_ptr<VersionPart> getRevision() const;
	void setRevision(std::shared_ptr<VersionPart> value);
private:
	void parse(const std::string& str);
	static void split(const std::string& input, char delimiter, std::vector<std::string>& elements);	
	std::shared_ptr<VersionPart> major;
	std::shared_ptr<VersionPart> minor;
	std::shared_ptr<VersionPart> build;
	std::shared_ptr<VersionPart> revision;
};

