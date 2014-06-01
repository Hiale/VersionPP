// VersionPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VersionPP.h"
#include "VersionFile.h"
#include "TransformerManager.h"
#include <fstream>
#include <iostream>

std::unique_ptr<TransformerManager> transformerManager;

int main(int argc, char *argv[])
{
	std::cout << "Version++, Version 0.5" << std::endl << "Copyright © 2014 Hiale" << std::endl;

	if (argc < 2) {
		std::cout << "Usage: \"" << argv[0] << "\" \"<filename.h>\"" << std::endl;
		std::cout << "Example: \"" << argv[0] << "\" \"C:\\dev\\proj\\version.h\"" << std::endl;
		std::cout << "This will patch the header file with the according version information." << std::endl;
		std::cout << "If the file does not exist a new template will be created." << std::endl;;
		std::cout << "Please check the Readme file for additional help." << std::endl;
		return 2;
	}

	std::string filename(argv[1]);
	if (!fileExists(filename)) {
		std::cout << "File \"" << filename << "\" does not exist. Creating template..." << std::endl;
		//ToDo
		return 0;
	}
	std::cout << "Reading \"" << filename << "\"..." << std::endl;

	transformerManager = std::unique_ptr<TransformerManager>(new TransformerManager);

	VersionFile inputFile(argv[1]);
	if (!inputFile.read()) {
		std::cout << "Application will exit now." << std::endl;
		return 1;
	}

	std::cout << "Analyzing file..." << std::endl;
	while (transformerManager->Transform(inputFile.getProductVersion(), inputFile.getCurrentProductVersion())) {
	}
	while (transformerManager->Transform(inputFile.getFileVersion(), inputFile.getCurrentFileVersion())) {
	}
	inputFile.replace();

	std::cout << "Writing..." << std::endl;
	if (!inputFile.write())
		return 1;

	std::cout << "Successful!" << std::endl;
	return 0;
}

bool fileExists(const std::string& filename)
{
	std::ifstream f(filename.c_str());
	return f.good();
}

