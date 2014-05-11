#include "stdafx.h"
#include "VersionFile.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <string>
#include <boost/algorithm/string.hpp>

VersionFile::VersionFile(std::string filename)
{
	file = std::unique_ptr<std::fstream>(new std::fstream);
	file->open(filename.c_str(), std::ios::in | std::ios::out);
	if (file->good())
		Read();
}

VersionFile::~VersionFile()
{
	file->close();
}

void VersionFile::Read()
{
	std::string line;
	std::regex pattern("(#[^\\S\\n]*define|\\/\\/)[^\\S\\n]([^\\s]+)[^\\S\\n]+([^\\s]+)", std::regex_constants::icase);
	while (std::getline(*file, line))
	{
		std::match_results<std::string::const_iterator> result;
		bool valid = std::regex_search(line, result, pattern);
		if (valid) {
			std::string prefix = result[1];
			std::string key = result[2];
			std::string keyUpper = boost::to_upper_copy(key);
			std::string version = result[3];
			if (boost::starts_with(prefix, "#") && boost::iequals(keyUpper, "PRODUCT_VERSION")) {
				currentProductVersion = std::unique_ptr<Version>(new Version(version));
			}
			else if (boost::starts_with(prefix, "#") && boost::iequals(keyUpper, "FILE_VERSION")) {
				currentFileVersion = std::unique_ptr<Version>(new Version(version));
			}
			else if (boost::starts_with(prefix, "//") && boost::iequals(keyUpper, "PRODUCTVERSION")) {
				productVersion = std::unique_ptr<Version>(new Version(version));
			}
			else if (boost::starts_with(prefix, "//") && boost::iequals(keyUpper, "FILEVERSION")) {
				fileVersion = std::unique_ptr<Version>(new Version(version));
			}
			else if (boost::starts_with(prefix, "//") && boost::iequals(keyUpper, "VERSION")) {
				productVersion = std::unique_ptr<Version>(new Version(version));
				fileVersion = std::unique_ptr<Version>(new Version(version));
			}			
		}
	}
}

void VersionFile::Write()
{

}
