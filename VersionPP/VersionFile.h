#pragma once

#include <string>
#include <memory>
#include "Version.h"

class VersionFile
{
public:
	VersionFile(std::string filename);	
	~VersionFile();
	void Write();
private:
	void Read();
	std::unique_ptr<std::fstream> file;
	std::unique_ptr<Version> productVersion;
	std::unique_ptr<Version> fileVersion;
};

