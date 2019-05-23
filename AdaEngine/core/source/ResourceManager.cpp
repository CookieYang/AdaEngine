#include "ResourceManager.h"
#include "GeometryData.h"
#include <fbxsdk.h>
#include <fbxsdk/core/fbxmanager.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <FreeImage.h>
#include "Engine.h"
#include "DefalutMaterial.h"

ResourceManager* ResourceManager::resManager = nullptr;
void loadGeometryModel(GeometryData*& raw, std::string path);
void processNode(GeometryData*& raw, aiNode* node, const aiScene* scene);
void processMesh(GeometryData*& raw, aiMesh* mesh, const aiScene* scene);


//RawResource* ResourceManager::loadTestCube() {
//	std::string cubePath("resource/Cube.OBJ");
//	//std::string texPath("resource/defalut.jpg");
//	//loadTextureFromFile(texPath);
//	return loadGeometryFromFile(cubePath);
//}



//RawResource* ResourceManager::loadTextureFromFile(std::string path) {
//	FreeImage_Initialise(TRUE);
//	FIBITMAP * JPEG = FreeImage_Load(FIF_JPEG, path.c_str(), JPEG_DEFAULT);
//	//获取影像的宽高，都以像素为单位
//	int Width = FreeImage_GetWidth(JPEG);
//	int Height = FreeImage_GetHeight(JPEG);
//	FreeImage_Unload(JPEG);
//	FreeImage_DeInitialise();
//	return nullptr;
//}

CPUResource* ResourceManager::loadResourceFromFile(std::string path, CPUResource::CResourceType type) {
	return nullptr;
}

Material* ResourceManager::createMaterial(std::string name, ShaderSource* shaderSource) {
	return nullptr;
}

ShaderSource* ResourceManager::createShaderSource(std::string name, const std::vector<std::string>& paths) {
	return nullptr;
}

TextureSource* ResourceManager::createTexture(std::string name, const std::string& path) {
	return nullptr;
}

MeshSource* ResourceManager::createMesh(std::string name, const std::string& path) {
	return nullptr;
}

GPUResource* ResourceManager::searchResourceByName(std::string name, GPUResource::GResourceType type) {
	return nullptr;
}

 static void loadGeometryModel(GeometryData*& raw, std::string path) {
	Assimp::Importer impoter;
	const aiScene* scene = impoter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		Engine::print(impoter.GetErrorString());
		return;
	}
	processNode(raw, scene->mRootNode, scene);
	//FbxManager* fbxManager = nullptr;
	//fbxManager = FbxManager::Create();
}

static void processNode(GeometryData*& raw, aiNode* node, const aiScene* scene) {
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
static void processMesh(GeometryData*& raw, aiMesh* mesh, const aiScene* scene) {
	GeometryData::VertexData vertexData;
	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		if (mesh->mVertices != nullptr)
		{
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertexData.vertexPosition.push_back(vector);
		}

		// normals
		if (mesh->mNormals != nullptr) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertexData.vertexNormal.push_back(vector);
		}

		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertexData.vertexUV.push_back(vec);
		}
		else
		{
			vertexData.vertexUV.push_back(glm::vec2(0.0f, 0.0f));
		}
		// tangent
		if (mesh->mTangents != nullptr) {
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertexData.vertexTangent.push_back(vector);
		}

		// bitangent
		if (mesh->mBitangents) {
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertexData.vertexBiTanget.push_back(vector);
		}
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			vertexData.vertexIndices.push_back(face.mIndices[j]);
	}
	GeometryData* geoVertexData = dynamic_cast<GeometryData*>(raw);
	geoVertexData->sectionsData.push_back(vertexData);
}

ResourceManager* ResourceManager::singleton() {
	if (resManager)
	{
		return resManager;
	}
	return nullptr;
}

ResourceManager::ResourceManager() {
	resManager = this;
}