#pragma once
#include "GPUResource.h"
#include "ShaderData.h"

class ShaderSource: public GPUResource {
	RefCountedPtr<ShaderData> mShaderData;
public:
	void setShaderData(ShaderData* shaderData);
	unsigned int program;
	std::vector<unsigned int> shaderIDs;
	ShaderSource();
	ShaderSource(ShaderData* shaderData);
	~ShaderSource();
};