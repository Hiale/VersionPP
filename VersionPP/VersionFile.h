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
	void setCurrentProductVersionString(std::string& value);
	void setCurrentFileVersionString(std::string& value);
private:	
	void prepareRead();
	bool checkVariable(std::unique_ptr<VersionFileItem>& targetItem, std::string& variableName);	
	bool createVersionFileItem(std::unique_ptr<VersionFileItem>& targetItem, std::string& variableName, std::string& versionValue, unsigned int lineNumber);
	void throwInvalidFile() const;
	std::string filename;
	std::unique_ptr<VersionFileItem> currentProductVersion;
	std::unique_ptr<VersionFileItem> currentFileVersion;
	std::unique_ptr<VersionFileItem> currentProductVersionString;
	std::unique_ptr<VersionFileItem> currentFileVersionString;
	std::unique_ptr<VersionFileItem> productVersion;
	std::unique_ptr<VersionFileItem> fileVersion;
	std::vector<std::string> fileContent;
};

