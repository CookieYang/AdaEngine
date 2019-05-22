#pragma once
#include "RefCountedPtr.h"
#include "TextureSource.h"
#include "ShaderSource.h"
#include <vector>

class Material : public RefCountable {
public:
	std::vector<RefCountedPtr<TextureSource>> textures;
	std::vector<std::string> textureNames;
	RefCountedPtr<ShaderSource> materialShader;
	Material() {};
	virtual ~Material() {};
};