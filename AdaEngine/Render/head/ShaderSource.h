#pragma once
#include "GPUResource.h"
#include "ShaderData.h"

class ShaderSource: public GPUResource {
	RefCountedPtr<ShaderData> mShaderData;
	bool dirty;
public:
	void setShaderData(const std::string& name);
	unsigned int program;
	std::vector<unsigned int> shaderIDs;
	ShaderSource();
	~ShaderSource();
};