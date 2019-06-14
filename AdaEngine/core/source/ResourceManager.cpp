#include "ResourceManager.h"
#include <fbxsdk.h>
#include <fbxsdk/core/fbxmanager.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "TextureData.h"
#include "ShaderData.h"
#include "GeometryData.h"
#include "Config.h"

ResourceManager* ResourceManager::resManager = nullptr;
void loadGeometryModel(GeometryData*& raw, std::string path);
void processNode(GeometryData*& raw, aiNode* node, const aiScene* scene);
void processMesh(GeometryData*& raw, aiMesh* mesh, const aiScene* scene);
void readMaterialDefalutValue(const MaterialVar::VarType& type, const rapidjson::Value& value, MaterialVar::VarData& data);

TextureData*  ResourceManager::loadTextureData(const std::string& path, const std::string& format) {
	FREE_IMAGE_FORMAT imageFormat;

	if (format == "PNG")
	{
		imageFormat = FIF_PNG;
	}
	else if (format == "JPG") {
		imageFormat = FIF_JPEG;
	}

	TextureData* tex = new TextureData;
	FIBITMAP * img = FreeImage_Load(imageFormat, path.c_str(), 0);
	int Width = FreeImage_GetWidth(img);
	int Height = FreeImage_GetHeight(img);
	tex->imageData = img;
	tex->height = Height;
	tex->width = Width;
	return tex;
}

GeometryData* ResourceManager::loadGeometryData(const std::string& path, const std::string& format) {
	if (format == "OBJ")
	{
		GeometryData* gData = new GeometryData;
		loadGeometryModel(gData, path);
		return gData;
	}
	else {
		return nullptr;
	}
}

ShaderData* ResourceManager::loadShaderDataFromFile(std::vector<std::string> paths, std::vector<std::string> types) {
	ShaderData* shader = new ShaderData;
	for (size_t i = 0; i < paths.size(); i++)
	{
		ShaderData::shaderString shaderFrag;
		if (types[i] == "VERTEXSHADER")
		{
			shaderFrag.shaderType = ShaderData::ShaderType::VERTEXSHADER;
		}
		else if (types[i] == "FRAGMENTSHADER") {
			shaderFrag.shaderType = ShaderData::ShaderType::FRAGMENTSHADER;
		}
		shaderFrag.shaderStr = readFileAsString(paths[i]);
		shader->shaderStrs.push_back(shaderFrag);
	}
	return shader;
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

Material* ResourceManager::createMaterial(const std::string& path) {
	// load Material
	Config matCig;
	matCig.loadJson(path);

	std::string name = matCig.asString("NAME");
	const rapidjson::Value& VS = matCig.asMap("VS");
	const rapidjson::Value& PS = matCig.asMap("PS");
	const rapidjson::Value& VSUniforms = VS.operator[]("UNIFORMS");
	const rapidjson::Value& PSUniforms = PS.operator[]("UNIFORMS");
	std::string vsPath = VS.operator[]("SHADERPATH").GetString();
	std::string vsType = VS.operator[]("SHADERTYPE").GetString();
	std::string psPath = PS.operator[]("SHADERPATH").GetString();
	std::string psType = PS.operator[]("SHADERTYPE").GetString();

	std::vector<std::string> paths;
	std::vector<std::string> types;

	paths.push_back(vsPath);
	paths.push_back(psPath);

	types.push_back(vsType);
	types.push_back(psType);

	ShaderSource* shader = new ShaderSource(ResourceManager::singleton()->loadShaderDataFromFile(paths, types));
	Material* m = new Material(shader);
	m->setName(name);

	for (rapidjson::Value::ConstMemberIterator itr = VSUniforms.MemberBegin();
		itr != VSUniforms.MemberEnd(); ++itr)
	{
		std::string uniformName = itr->name.GetString();
		// location 0 means uniform type
		MaterialVar::VarType varType = UNIFORMCONVERTMAP.at(itr->value[0].GetString());
		// location 1 means defalut value
		MaterialVar::VarData defalutValue;
		readMaterialDefalutValue(varType, itr->value[1], defalutValue);
		m->uniforms[uniformName] = std::make_pair(varType, defalutValue);
	}

	for (rapidjson::Value::ConstMemberIterator itr = PSUniforms.MemberBegin();
		itr != PSUniforms.MemberEnd(); ++itr)
	{
		std::string uniformName = itr->name.GetString();
		MaterialVar::VarType varType = UNIFORMCONVERTMAP.at(itr->value[0].GetString());
		MaterialVar::VarData defalutValue;
		readMaterialDefalutValue(varType, itr->value[1], defalutValue);
		m->uniforms[uniformName] = std::make_pair(varType, defalutValue);
	}
	MaterialMap[m->getName()] = m;
	return m;
}

TextureSource* ResourceManager::createTexture(const std::string& path) {
	TextureSource* tex = new TextureSource(path);
	TextureSourceMap[tex->getName()] = tex;
	return tex;
}

MeshSource* ResourceManager::createMesh(const std::string& path) {
	MeshSource* mesh = new MeshSource(path);
	MeshSourceMap[mesh->getName()] = mesh;
	return mesh;
}

MaterialInstance* ResourceManager::createMaterialInstance(const std::string& matInstanceName, const std::string& matName) {
	MaterialInstance* matInstance = new MaterialInstance;
	Material* m = (Material*)this->GetResourceByName(matName, GPUResource::GResourceType::MATRERIAL);
	matInstance->mat = m;
	matInstance->setName(matInstanceName);

	for (auto uniform : m->uniforms) {
		MaterialVar var;
		var.mType = uniform.second.first;
		var.mVar = uniform.second.second;
		matInstance->materialVars[uniform.first] = var;
	}
	MaterialInstanceMap[matInstanceName] = matInstance;
	return matInstance;
}

GPUResource* ResourceManager::GetResourceByName(const std::string& name, GPUResource::GResourceType type) {
	GPUResource* resource = nullptr;
	switch (type)
	{
	case GPUResource::MESH:
		resource = MeshSourceMap[name].get();
		break;
	case GPUResource::TEXTURE:
		resource = TextureSourceMap[name];
		break;
	case GPUResource::MATRERIAL:
		resource = MaterialMap[name].get();
		break;
	case GPUResource::MATERIALINS:
		resource = MaterialInstanceMap[name];
		break;
	default:
		break;
	}
	return resource;
}

std::string ResourceManager::readFileAsString(const std::string& path) {
	std::ifstream ifile(path);
	std::ostringstream buf;
	char ch;
	while (buf&&ifile.get(ch))
		buf.put(ch);
	return buf.str();
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

void readMaterialDefalutValue(const MaterialVar::VarType& type, const rapidjson::Value& value, MaterialVar::VarData& data) {
	switch (type)
	{
	case MaterialVar::VarType::MAT4:
	{
		float mat4[16];
		int index = 0;
		for (auto& v : value.GetArray()) {
			mat4[index] = v.GetFloat();
			index++;
		}
		data.mat4 = glm::make_mat4x4(mat4);
	}
	break;
	case MaterialVar::VarType::TEXTURE2D:
	{
		std::string* textureName = new std::string(value.GetString());
		data.texName = textureName;
	}
	break;
	default:
		break;
	}
}