#pragma once
#include "GPUResource.h"
#include "CPUResource.h"
#include <map>

class aiNode;
class aiScene;
class aiMesh;
class DefalutMaterial;
class MeshSource;
class Material;
class ShaderSource;
class TextureSource;

class ResourceManager {
	std::map<std::string, CPUResource*> loadedResource;   // cpu resources 
	std::map<std::string, Material*> loadedMaterials;
	std::map<std::string, MeshSource*> loadedMeshes;
	std::map<std::string, ShaderSource*> loadedShaders;
	std::map<std::string, TextureSource*> loadedTextures;
	static ResourceManager* resManager;
	CPUResource* loadResourceFromFile(std::string path, CPUResource::CResourceType type);
public:
	static ResourceManager* singleton();
	GPUResource* createResourceByType(std::string name, GPUResource::GResourceType type);             // must create new one
	GPUResource* searchResourceByName(std::string name, GPUResource::GResourceType type);          // try to copy first
	ResourceManager();
	~ResourceManager() {};
};