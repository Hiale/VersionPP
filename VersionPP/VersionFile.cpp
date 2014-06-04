#include "stdafx.h"
#include "VersionFile.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>

VersionFile::VersionFile(std::string filename) : filename(filename), lineVariableMap(), fileContent()
{	
}

VersionFile::~VersionFile()
{
}

bool VersionFile::read()
{
	std::ifstream file;
	file.open(filename.c_str());
	if (!file.good())
		return false;
	prepareRead();
	std::string line;
	std::regex pattern("(#[^\\S\\n]*define|\\/\\/)[^\\S\\n]*([^\\s]+)[^\\S\\n]+([^\\s]+)", std::regex_constants::icase);
	unsigned int lineNumber = 0;
	while (std::getline(file, line))
	{
		fileContent.push_back(line);
		std::match_results<std::string::const_iterator> result;
		bool valid = std::regex_search(line, result, pattern);
		if (valid) {
			std::string prefix = result[1];
			std::string variableName = result[2];
			std::string variableNameUpper = boost::to_upper_copy(variableName);
			std::string versionValue = result[3];
			unsigned int versionValueLength = result.length(3);
			unsigned int linePosition = result.position(3);			

			if (boost::starts_with(prefix, "#") && boost::iequals(variableNameUpper, "PRODUCT_VERSION")) {
				if (!createVersionFileItem(currentProductVersion, variableName, versionValue, versionValueLength, lineNumber, linePosition))
					return false;
			}
			else if (boost::starts_with(prefix, "#") && boost::iequals(variableNameUpper, "FILE_VERSION")) {
				if (!createVersionFileItem(currentFileVersion, variableName, versionValue, versionValueLength, lineNumber, linePosition))
					return false;
			}
			else if (boost::starts_with(prefix, "#") && boost::iequals(variableNameUpper, "PRODUCT_VERSION_STRING")) {				
				currentProductVersionString = std::make_shared<VersionFileItem>(versionValue, versionValueLength, lineNumber, linePosition, false);
				lineVariableMap.insert(std::pair<unsigned int, std::shared_ptr<VersionFileItem>>(lineNumber, currentProductVersionString));
			}
			else if (boost::starts_with(prefix, "#") && boost::iequals(variableNameUpper, "FILE_VERSION_STRING")) {
				currentFileVersionString = std::make_shared<VersionFileItem>(versionValue, versionValueLength, lineNumber, linePosition, false);
				lineVariableMap.insert(std::pair<unsigned int, std::shared_ptr<VersionFileItem>>(lineNumber, currentFileVersionString));
			}
			else if (boost::starts_with(prefix, "//") && boost::iequals(variableNameUpper, "PRODUCTVERSION")) {
				if (!createVersionFileItem(productVersion, variableName, versionValue, versionValueLength, lineNumber, linePosition))
					return false;
			}
			else if (boost::starts_with(prefix, "//") && boost::iequals(variableNameUpper, "FILEVERSION")) {
				if (!createVersionFileItem(fileVersion, variableName, versionValue, versionValueLength, lineNumber, linePosition))
					return false;
			}
			else if (boost::starts_with(prefix, "//") && boost::iequals(variableNameUpper, "VERSION")) {
				if (productVersion) {
					std::cout << "The variable '" << variableName << "' is ignored because the product version is already defined." << std::endl;
				}
				else {
					if (!createVersionFileItem(productVersion, variableName, versionValue, versionValueLength, lineNumber, linePosition))
						return false;
				}
				if (fileVersion) {
					std::cout << "The variable '" << variableName << "' is ignored because the file version is already defined." << std::endl;
				}
				else {
					if (!createVersionFileItem(fileVersion, variableName, versionValue, versionValueLength, lineNumber, linePosition))
						return false;
				}
			}
		}
		lineNumber++;
	}

	if (!checkVariable(currentProductVersion, std::string("PRODUCT_VERSION")))
		return false;
	if (!checkVariable(currentFileVersion, std::string("FILE_VERSION")))
		return false;
	if (!checkVariable(productVersion, std::string("ProductVersion or Version")))
		return false;
	if (!checkVariable(fileVersion, std::string("FileVersion or Version")))
		return false;

	return true;
}

bool VersionFile::write()
{
	std::ofstream file;
	file.open(filename.c_str(), std::ios::trunc);
	if (!file.good())
		return false;

	for (std::vector<std::string>::size_type i = 0; i != fileContent.size(); i++) {
		file << fileContent[i] << std::endl;
	}
	return true;
}

bool VersionFile::createVersionFileItem(std::shared_ptr<VersionFileItem>& targetItem, std::string& variableName, std::string& versionValue, unsigned int versionValueLength, unsigned int lineNumber, unsigned int linePosition)
{
	try {
		targetItem = std::make_shared<VersionFileItem>(versionValue, versionValueLength, lineNumber, linePosition);
		lineVariableMap.insert(std::pair<unsigned int, std::shared_ptr<VersionFileItem>>(lineNumber, targetItem));
	}
	catch (...) {
		std::cout << "Variable " << variableName << " has an invalid format." << std::endl;
		return false;
	}
	return true;
}

void VersionFile::prepareRead()
{
	lineVariableMap.clear();
	fileContent.clear();
	currentProductVersion.reset();
	currentFileVersion.reset();
	productVersion.reset();
	fileVersion.reset();
}

bool VersionFile::checkVariable(std::shared_ptr<VersionFileItem>& targetItem, std::string& variableName)
{
	if (!targetItem) {
		std::cout << "The variable " << variableName << " is not defined." << std::endl;
		return false;
	}
	return true;
}

Version& VersionFile::getCurrentProductVersion() const
{
	if (currentProductVersion)
		return currentProductVersion->getVersion();
	throwInvalidFile();
}

Version& VersionFile::getCurrentFileVersion() const
{
	if (currentFileVersion)
		return currentFileVersion->getVersion();
	throwInvalidFile();
}

Version& VersionFile::getProductVersion() const
{
	if (productVersion)
		return productVersion->getVersion();
	throwInvalidFile();
}

Version& VersionFile::getFileVersion() const
{
	if (fileVersion)
		return fileVersion->getVersion();
	throwInvalidFile();
}

void VersionFile::throwInvalidFile() const
{
	throw std::exception("Load file first or file is invalid.");
}

void VersionFile::replace()
{
	currentProductVersion->setReplacementValue(productVersion->getVersion().ToStrictString(","));
	currentProductVersionString->setReplacementValue("\"" + productVersion->getVersion().ToString(".") + "\"");

	currentFileVersion->setReplacementValue(fileVersion->getVersion().ToStrictString(","));
	currentFileVersionString->setReplacementValue("\"" + fileVersion->getVersion().ToString(".") + "\"");

	for (std::vector<int>::size_type i = 0; i != fileContent.size(); i++) {
		std::map<unsigned int, std::shared_ptr<VersionFileItem>>::iterator it = lineVariableMap.find(i);
		if (it != lineVariableMap.end())
		{
			std::shared_ptr<VersionFileItem> versionInfo = it->second;
			if (versionInfo->getReplacementValue() == "" || versionInfo->getReplacementValue() == versionInfo->getOriginalValue())
				continue;
			fileContent[i].replace(versionInfo->getLinePosition(), versionInfo->getOriginalValueLength(), versionInfo->getReplacementValue());
		}
	}
}