#include "ResourceManager.h"
#include <fbxsdk.h>
#include <fbxsdk/core/fbxmanager.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <fstream>
#include <sstream>
#include <iostream>

ResourceManager* ResourceManager::resManager = nullptr;
void loadGeometryModel(GeometryData*& raw, std::string path);
void processNode(GeometryData*& raw, aiNode* node, const aiScene* scene);
void processMesh(GeometryData*& raw, aiMesh* mesh, const aiScene* scene);
std::string readFileToString(const std::string& path);

CPUResource* ResourceManager::loadTextureFromFile(const std::string& name, const std::string& path, FREE_IMAGE_FORMAT imageFormat, int loadFlag) {
	TextureData* tex = new TextureData;
	FIBITMAP * img = FreeImage_Load(imageFormat, path.c_str(), loadFlag);
	int Width = FreeImage_GetWidth(img);
	int Height = FreeImage_GetHeight(img);
	tex->setName(name);
	tex->setResPath(path);
	tex->imageData = img;
	tex->height = Height;
	tex->width = Width;
	loadedResource.insert(std::pair<std::string, RefCountedPtr<CPUResource>>(tex->getName(), tex));
	return tex;
}

CPUResource* ResourceManager::loadGeometryResourceFromFile(const std::string& name, const std::string& path) {
	GeometryData* gData = new GeometryData;
	loadGeometryModel(gData, path);
	gData->setName(name);
	gData->setResPath(path);
	loadedResource.insert(std::pair<std::string, RefCountedPtr<CPUResource>>(gData->getName(), gData));
	return gData;
}

std::string readFileToString(const std::string& path) {
	std::ifstream ifile(path);
	//将文件读入到ostringstream对象buf中
	std::ostringstream buf;
	char ch;
	while (buf&&ifile.get(ch))
		buf.put(ch);
	//返回与流对象buf关联的字符串
	return buf.str();
}

CPUResource* ResourceManager::loadShaderGroupFromFile(const std::string& name) {
	ShaderData* shader = new ShaderData;
	shader->setName(name);
	ShaderData::shaderString shaderFrag1;
	shaderFrag1.shaderType = ShaderData::ShaderType::VERTEXSHADER;
	shaderFrag1.shaderStr = readFileToString("shaders/forward/defalut_fs.glsl");
	ShaderData::shaderString shaderFrag2;
	shaderFrag2.shaderType = ShaderData::ShaderType::FRAGMENTSHADER;
	shaderFrag2.shaderStr = readFileToString("shaders/forward/defalut_ps.glsl");
	shader->shaderStrs.push_back(shaderFrag1);
	shader->shaderStrs.push_back(shaderFrag2);
	loadedResource.insert(std::pair<std::string, RefCountedPtr<CPUResource>>(shader->getName(), shader));
	return shader;
}

CPUResource* ResourceManager::GetResourceByName(const std::string& name) {
	CPUResource* res = nullptr;
	res = loadedResource[name].get();
	return res;
}

 static void loadGeometryModel(GeometryData*& raw, std::string path) {
	Assimp::Importer impoter;
	const aiScene* scene = impoter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		
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

	if (mesh->mVertices != nullptr)
	{
		raw->vboSize++;
	}
	raw->vboSize++;
	if (mesh->mNormals != nullptr) {
		raw->vboSize++;
	}
	if (mesh->mTangents != nullptr) {
		raw->vboSize++;
	}
	if (mesh->mBitangents) {
		raw->vboSize++;
	}
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
	FreeImage_Initialise(TRUE);
}

ResourceManager::~ResourceManager() {
	FreeImage_DeInitialise();
}