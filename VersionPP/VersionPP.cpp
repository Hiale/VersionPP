// VersionPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DotNetVersion.h"
#include "VersionFile.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "Version++, Version 0.1" << std::endl << "Copyright � 2014 Hiale" << std::endl;

	VersionFile inputFile("S:\\Visual Studio Projects\\VersionPP\\VersionPP\\TestFile.h");

	return 0;

	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	int build = 0;
	int revision = 0;
	DotNetVersion::CalculateBuildRevision(now, build, revision);

	boost::posix_time::ptime dt = DotNetVersion::CalculateBuildTime(5234, 3389);

	std::cout << dt;

	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <filename> <arguments>" << std::endl;
		std::cout << "Example: " << argv[0] << " C:\\dev\\proj\\version.h -VERSION 0.5.*.*";
		std::cout << "Please check the Readme file for additional help.";
			/*std::cout << "This will open the <filename> update the version information.";
			std::cout << "If the file does not exist, a new template file will be created.";
			std::cout << "You can specify the -VERSION command, which will set the version directly.";
			std::cout << "Product and file version can be set individually using the -PRODUCT_VERSION and - FILE_VERSION commands.";
			std::cout << "Versions include four parts: Mayor, Minor, Build and Revision. Example: 1.2.3.4";
			std::cout << "You can use * in the build and revision parts. Example 1.2.*.*";
			std::cout << "In this case, the .NET assembly version algorithm is used.";*/



	}

	return 0;
}

