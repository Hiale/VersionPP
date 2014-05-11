#pragma once

#include <vector>
#include <memory>
#include "Transformer.h"
#include "Version.h"

class TransformerManager
{
public:
	TransformerManager();
	~TransformerManager();
	bool Transform(Version& version);
private:
	void load();
	std::vector<std::unique_ptr<Transformer>> items;
};

