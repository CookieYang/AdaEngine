#pragma once
#include "RawResource.h"
#include <map>
#include <functional>

class aiNode;
class aiScene;
class aiMesh;
class DefalutMaterial;

class ResourceManager {
	std::map<size_t, RawResource*> loadedResource;   // raw resources
	std::hash<std::string> stringHash;
	static ResourceManager* resManager;
	void loadGeometryModel(RawResource*& raw, std::string path);
	void processNode(RawResource*& raw, aiNode* node, const aiScene* scene);
	void processMesh(RawResource*& raw, aiMesh* mesh, const aiScene* scene);

	DefalutMaterial* defalutMaterial;
public:
	static ResourceManager* singleton();
	RawResource* loadTestCube();
	DefalutMaterial* loadDefalutMaterial();
	RawResource* loadGeometryFromFile(std::string path);
	RawResource* loadTextureFromFile(std::string path);
	ResourceManager();
	~ResourceManager() {};
};