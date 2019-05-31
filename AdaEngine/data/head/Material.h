#pragma once
#include "GPUResource.h"
#include "TextureSource.h"
#include "ShaderSource.h"
#include <vector>
#include <map>
#include <glm/glm.hpp>

class MeshSection;
class Material : public GPUResource {
	RefCountedPtr<ShaderSource> materialShader;
	volatile bool dirty;
public:
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
		unsigned int* texID;  
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
		BOOL,
		TEXTURE2D
	};
	VarType mType;
	VarData mVar;
	MaterialVar() {};
	~MaterialVar() {};
	MaterialVar(const glm::mat4& var) { mVar.mat4 = var; mType = VarType::MAT4; };
	MaterialVar(const glm::mat3& var) { mVar.mat3 = var; mType = VarType::MAT3; };
	MaterialVar(const glm::vec4& var) { mVar.vec4 = var; mType = VarType::VEC4; };
	MaterialVar(const glm::vec3& var) { mVar.vec3 = var; mType = VarType::VEC3; };
	MaterialVar(const glm::vec2& var) { mVar.vec2 = var; mType = VarType::VEC2; };
	MaterialVar(float var) { mVar.f = var; mType = VarType::FLOAT; };
	MaterialVar(bool var) { mVar.b = var; mType = VarType::BOOL; };
	MaterialVar(int var) { mVar.i = var; mType = VarType::INT; };
	MaterialVar(unsigned int* var) { mVar.texID = var; mType = VarType::TEXTURE2D; };
};

class MaterialInstance : public GPUResource {
public:
	std::vector<RefCountedPtr<TextureSource>> textureRefs; // for release count (when there are too much texture existing)
	std::map<std::string, MaterialVar> materialVars;
	void attachTexture(const std::string& name);
	Material* mat;
};