#pragma once
#include "GPUResource.h"
#include "TextureSource.h"
#include "ShaderSource.h"
#include <vector>
#include <string>
#include <list>

class MeshSection;
class Material : public GPUResource {
public:
	std::vector<RefCountedPtr<TextureSource>> textures;
	std::vector<std::string> textureNames;
	RefCountedPtr<ShaderSource> materialShader;
	std::list<MeshSection*> meshRefs;
	Material() {};
	virtual ~Material() {};
};