#pragma once
#include "RawResource.h"
#include <map>
#include <functional>

class aiNode;
class aiScene;
class aiMesh;

class ResourceManager {
	std::map<size_t, RawResource*> loadedResource;   // raw resources
	std::hash<std::string> stringHash;
	void loadGeometryModel(RawResource*& raw, std::string path);
	void processNode(RawResource*& raw, aiNode* node, const aiScene* scene);
	void processMesh(RawResource*& raw, aiMesh* mesh, const aiScene* scene);
public:
	RawResource* loadTestCube();
	RawResource* loadGeometryFromFile(std::string path);
};