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
		if (transformer->Transform(version, currentVersion))
			processed = true;
	}
	return processed;
}

void TransformerManager::load()
{
	items.push_back(std::unique_ptr<Transformer>(new DotNetTransformer));
	items.push_back(std::unique_ptr<Transformer>(new IncrementResetTransformer));
	items.push_back(std::unique_ptr<Transformer>(new IncrementAlwaysTransformer));
}