#pragma once
#include "RawResource.h"
#include <map>
#include <functional>

class ResourceManager {
	std::map<size_t, RawResource*> loadedResource;   // raw resources
	std::hash<std::string> stringHash;
public:
	RawResource * loadTestCube();
};