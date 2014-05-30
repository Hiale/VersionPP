#pragma once

#include <memory>
#include "TransformerManager.h"

bool fileExists(const std::string& filename);

extern std::unique_ptr<TransformerManager> transformerManager;