#pragma once

#include <vector>
#include <memory>
#include "ITransformer.h"
#include "Version.h"

class TransformerManager
{
public:
	TransformerManager();
	~TransformerManager();
	bool Transform(Version& version);
private:
	void load();
	std::vector<std::unique_ptr<ITransformer>> items;
};

