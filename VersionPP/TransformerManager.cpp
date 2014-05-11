#include "stdafx.h"
#include "TransformerManager.h"
#include "DotNetTransformer.h"

TransformerManager::TransformerManager()
{
	load();
}

TransformerManager::~TransformerManager()
{
}

bool TransformerManager::Transform(Version& version)
{
	bool processed = false; //at least one transformer processed the version.
	for (const std::unique_ptr<ITransformer>& transformer : items) {
		if (!version.containsIdentifier(transformer->getIdentifier()))
			continue;
		if (transformer->Transform(version))
			processed = true;
	}
	return processed;
}

void TransformerManager::load()
{
	items.push_back(std::unique_ptr<ITransformer>(new DotNetTransformer));
}