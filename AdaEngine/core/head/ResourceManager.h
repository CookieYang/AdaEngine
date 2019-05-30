#pragma once
#include "GPUResource.h"
#include "CPUResource.h"
#include "TextureData.h"
#include "ShaderData.h"
#include "GeometryData.h"
#include <map>
#include <vector>
#include <FreeImage.h>

class aiNode;
class aiScene;
class aiMesh;

class ResourceManager {
	std::map<std::string, RefCountedPtr<CPUResource>> loadedResource;   // cpu resources 
	static ResourceManager* resManager;
public:
	CPUResource* loadTextureFromFile(const std::string& name, const std::string& path, FREE_IMAGE_FORMAT imageFormat, int loadFlag);
	CPUResource* loadGeometryResourceFromFile(const std::string& name, const std::string& path);
	CPUResource* loadShaderGroupFromFile(const std::string& name);
	CPUResource* GetResourceByName(const std::string& name);
	static ResourceManager* singleton();
	ResourceManager();
	~ResourceManager();
};