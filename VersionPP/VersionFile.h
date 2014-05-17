#pragma once

#include <string>
#include <memory>
#include "VersionFileItem.h"

class VersionFile
{
public:
	VersionFile(std::string filename);	
	~VersionFile();
	bool read();
	bool write();
	Version& getCurrentProductVersion() const;
	Version& getCurrentFileVersion() const;
	Version& getProductVersion() const;
	Version& getFileVersion() const;
private:	
	void prepareRead();
	bool checkVariable(std::unique_ptr<VersionFileItem>& targetItem, std::string& variableName);	
	bool createVersionFileItem(std::unique_ptr<VersionFileItem>& targetItem, std::string& variableName, std::string& versionValue, unsigned int lineNo);
	void throwInvalidFile() const;
	std::unique_ptr<std::fstream> file;
	std::unique_ptr<VersionFileItem> currentProductVersion;
	std::unique_ptr<VersionFileItem> currentFileVersion;
	std::unique_ptr<VersionFileItem> productVersion;
	std::unique_ptr<VersionFileItem> fileVersion;
};

