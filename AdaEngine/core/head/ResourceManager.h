#pragma once
#include "GPUResource.h"
#include <map>
#include <vector>
#include <FreeImage.h>
#include "Material.h"
#include "TextureSource.h"
#include "MeshSource.h"

class aiNode;
class aiScene;
class aiMesh;
class TextureData;
class GeometryData;
class shaderData;


class ResourceManager {
	static ResourceManager* resManager;
	std::map<std::string, RefCountedPtr<Material>> MaterialMap;
	std::map<std::string, RefCountedPtr<MeshSource>> MeshSourceMap;
	std::map<std::string, TextureSource*> TextureSourceMap;
	std::map<std::string, MaterialInstance*> MaterialInstanceMap;
public:
	TextureData* loadTextureData(const std::string& path, const std::string& format);
	GeometryData* loadGeometryData(const std::string& path, const std::string& format);
	ShaderData* loadShaderDataFromFile(std::vector<std::string> paths, std::vector<std::string> types);
	Material* createMaterial(const std::string& path);
	TextureSource* createTexture(const std::string& path);
	MeshSource* createMesh(const std::string& path);
	MaterialInstance* createMaterialInstance(const std::string& matInstanceName, const std::string& matName);
	GPUResource* GetResourceByName(const std::string& name, GPUResource::GResourceType type);
	static std::string readFileAsString(const std::string& path);
	static ResourceManager* singleton();
	ResourceManager();
	~ResourceManager();
};