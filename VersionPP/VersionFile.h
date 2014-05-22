#pragma once

#include <string>
#include <map>
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
	bool checkVariable(std::shared_ptr<VersionFileItem>& targetItem, std::string& variableName);	
	bool createVersionFileItem(std::shared_ptr<VersionFileItem>& targetItem, std::string& variableName, std::string& versionValue, unsigned int lineNumber, unsigned int linePosition);
	void throwInvalidFile() const;
	std::string filename;
	std::shared_ptr<VersionFileItem> currentProductVersion;
	std::shared_ptr<VersionFileItem> currentFileVersion;
	std::shared_ptr<VersionFileItem> currentProductVersionString;
	std::shared_ptr<VersionFileItem> currentFileVersionString;
	std::shared_ptr<VersionFileItem> productVersion;
	std::shared_ptr<VersionFileItem> fileVersion;
	std::map<unsigned int, std::shared_ptr<VersionFileItem>> lineVariableMap;
	std::vector<std::string> fileContent;
};

