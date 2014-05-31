#include "stdafx.h"
#include "TransformerManager.h"
#include "DotNetTransformer.h"
#include "IncrementResetTransformer.h"
#include "IncrementAlwaysTransformer.h"

TransformerManager::TransformerManager()
{
	load();
}

TransformerManager::~TransformerManager()
{
}

bool TransformerManager::Transform(Version& version, const Version& currentVersion)
{
	bool processed = false; //at least one transformer processed the version.
	for (const std::unique_ptr<Transformer>& transformer : items) {
		if (!version.containsIdentifier(transformer->getIdentifier()))
			continue;
		try
		{
			if (transformer->Transform(version, currentVersion))
				processed = true;
		}
		catch (std::exception& e)
		{
			std::cout << "Error:" << std::endl << "Transformer: " << transformer->getName() << std::endl << "Version: " << version.ToString(".") << std::endl << e.what() << std::endl;
		}
		
	}
	return processed;
}

void TransformerManager::load()
{
	items.push_back(std::unique_ptr<Transformer>(new DotNetTransformer));
	items.push_back(std::unique_ptr<Transformer>(new IncrementResetTransformer));
	items.push_back(std::unique_ptr<Transformer>(new IncrementAlwaysTransformer));
}