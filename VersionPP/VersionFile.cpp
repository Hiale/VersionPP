#include "stdafx.h"
#include "VersionFile.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>

VersionFile::VersionFile(std::string filename)
{
	file = std::unique_ptr<std::fstream>(new std::fstream);
	file->open(filename.c_str(), std::ios::in | std::ios::out);
	if (file->good())
		read();
}

VersionFile::~VersionFile()
{
	file->close();
}

bool VersionFile::read()
{
	prepareRead();
	std::string line;
	std::regex pattern("(#[^\\S\\n]*define|\\/\\/)[^\\S\\n]([^\\s]+)[^\\S\\n]+([^\\s]+)", std::regex_constants::icase);
	unsigned int lineNo = 0;
	while (std::getline(*file, line))
	{
		std::match_results<std::string::const_iterator> result;
		bool valid = std::regex_search(line, result, pattern);
		if (valid) {
			std::string prefix = result[1];
			std::string variableName = result[2];
			std::string variableNameUpper = boost::to_upper_copy(variableName);
			std::string versionValue = result[3];

			if (boost::starts_with(prefix, "#") && boost::iequals(variableNameUpper, "PRODUCT_VERSION")) {
				if (!createVersionFileItem(currentProductVersion, variableName, versionValue, lineNo))
					return false;
			}
			else if (boost::starts_with(prefix, "#") && boost::iequals(variableNameUpper, "FILE_VERSION")) {
				if (!createVersionFileItem(currentFileVersion, variableName, versionValue, lineNo))
					return false;
			}
			else if (boost::starts_with(prefix, "//") && boost::iequals(variableNameUpper, "PRODUCTVERSION")) {
				if (!createVersionFileItem(productVersion, variableName, versionValue, lineNo))
					return false;
			}
			else if (boost::starts_with(prefix, "//") && boost::iequals(variableNameUpper, "FILEVERSION")) {
				if (!createVersionFileItem(fileVersion, variableName, versionValue, lineNo))
					return false;
			}
			else if (boost::starts_with(prefix, "//") && boost::iequals(variableNameUpper, "VERSION")) {
				if (productVersion) {
					std::cout << "The variable " << variableName << " is ignored because the version is already defined.";
				}
				else {
					if (!createVersionFileItem(productVersion, variableName, versionValue, lineNo))
						return false;
				}
				if (fileVersion) {
					std::cout << "The variable " << variableName << " is ignored because the version is already defined.";
				}
				else {
					if (!createVersionFileItem(fileVersion, variableName, versionValue, lineNo))
						return false;
				}
			}
		}
		lineNo++;
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

void VersionFile::write()
{

}

bool VersionFile::createVersionFileItem(std::unique_ptr<VersionFileItem>& targetItem, std::string& variableName, std::string& versionValue, unsigned int lineNo)
{
	try {
		targetItem = std::unique_ptr<VersionFileItem>(new VersionFileItem(versionValue, lineNo));
	}
	catch (...) {
		std::cout << "Variable " << variableName << " has an invalid format.";
		return false;
	}
	return true;
}

void VersionFile::prepareRead()
{
	currentProductVersion.reset();
	currentFileVersion.reset();
	productVersion.reset();
	fileVersion.reset();
}

bool VersionFile::checkVariable(std::unique_ptr<VersionFileItem>& targetItem, std::string& variableName)
{
	if (!targetItem) {
		std::cout << "The variable " << variableName << " is not defined.";
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
