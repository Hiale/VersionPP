#include "stdafx.h"
#include "VersionFile.h"
#include <iostream>
#include <fstream>
#include <regex>

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
	std::regex pattern("\\/\\/ *(\\b.+\\b) +(\\b.+\\b)", std::regex_constants::icase);
	while (std::getline(*file, line))
	{
		std::match_results<std::string::const_iterator> result;
		bool valid = std::regex_search(line, result, pattern);
		if (valid) {
			std::string key = result[1];
			std::string version = result[2];
		}
	}
}

void VersionFile::Write()
{

}
