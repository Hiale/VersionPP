#pragma once

#include <string>
#include <memory>
#include "VersionFileItem.h"

class VersionFile
{
public:
	VersionFile(std::string filename);	
	~VersionFile();
	void Write();
private:
	void Read();
	std::unique_ptr<std::fstream> file;
	std::unique_ptr<VersionFileItem> currentProductVersion;
	std::unique_ptr<VersionFileItem> currentFileVersion;
	std::unique_ptr<VersionFileItem> productVersion;
	std::unique_ptr<VersionFileItem> fileVersion;
};

