#include "ResourceManager.h"
#include "GeometryData.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Engine.h"

RawResource* ResourceManager::loadTestCube() {
	std::string cubePath("..\\resource\\Cube.OBJ");
	return loadGeometryFromFile(cubePath);
}

RawResource* ResourceManager::loadGeometryFromFile(std::string path) {
	size_t hash = stringHash(path);
	auto it = loadedResource.find(hash);
	RawResource* p = nullptr;
	if (it != loadedResource.end()) {
		if (it->second != nullptr) {
			return it->second;
		}
		else {
			// load from file
			p = new GeometryData;
			loadGeometryModel(p, path);
			it->second = p;
			return p;
		}
	}
	else {
		// load from file
		p = new GeometryData;
		loadGeometryModel(p, path);
		loadedResource.insert(std::pair<size_t, RawResource*>(hash, p));
		return p;
	}
}

void ResourceManager::loadGeometryModel(RawResource*& raw, std::string path) {
	Assimp::Importer impoter;
	const aiScene* scene = impoter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		Engine::print(impoter.GetErrorString());
		return;
	}
	processNode(raw, scene->mRootNode, scene);
}

void ResourceManager::processNode(RawResource*& raw, aiNode* node, const aiScene* scene) {
	// Process each mesh located at the current node
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		// The node object only contains indices to index the actual objects in the scene. 
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(raw, mesh, scene);
	}
	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		processNode(raw, node->mChildren[i], scene);
	}
}
void ResourceManager::processMesh(RawResource*& raw, aiMesh* mesh, const aiScene* scene) {

}