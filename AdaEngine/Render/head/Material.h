#pragma once
#include "GPUResource.h"
#include "TextureSource.h"
#include "ShaderSource.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>

class MeshSection;
class Material : public GPUResource {
	RefCountedPtr<ShaderSource> materialShader;
	volatile bool dirty;
public:
	std::string passName;
	void attachShader(ShaderSource* shader);
	void attachToMeshSection(MeshSection* meshSection);
	ShaderSource* getShader();
	Material():dirty(true) {};
	virtual ~Material() {};
	std::vector<MeshSection*> meshRefs;
	bool getDirty();
	void setDirty(bool dirty);
};

struct MaterialVar
{
	union VarData
	{
		glm::mat4 mat4;
		glm::mat3 mat3;
		glm::vec4 vec4;
		glm::vec3 vec3;
		glm::vec2 vec2;
		float f;
		int i;
		bool b;
	};
	enum VarType
	{
		MAT4,
		MAT3,
		VEC4,
		VEC3,
		VEC2,
		FLOAT,
		INT,
		BOOL
	};
	VarType mType;
	VarData mVar;
	std::string bindingName;
};

class MaterialInstance : public GPUResource {
public:
	std::vector<RefCountedPtr<TextureSource>> textureIDs;          // copys
	std::vector<MaterialVar> materialVars;
	void attachTexture(const std::string& name);
	Material* mat;
};