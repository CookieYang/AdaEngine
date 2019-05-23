#pragma once
#include "GPUResource.h"
#include "CPUResource.h"
#include <map>
#include <vector>

class aiNode;
class aiScene;
class aiMesh;

class ResourceManager {
	std::map<std::string, CPUResource*> loadedResource;   // cpu resources 
	static ResourceManager* resManager;
	CPUResource* loadResourceFromFile(std::string path, CPUResource::CResourceType type);
public:
	static ResourceManager* singleton();
	ResourceManager();
	~ResourceManager() {};
};