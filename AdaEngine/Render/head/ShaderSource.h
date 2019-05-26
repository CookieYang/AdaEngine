#pragma once
#include "GPUResource.h"
#include "ShaderData.h"

class ShaderSource: public GPUResource {
	RefCountedPtr<ShaderData> mShaderData;
	bool dirty;
public:
	bool getDirty();
	void setDirty(bool dirty);
	void setShaderData(const std::string& name);
	ShaderData* getShaderData();
	unsigned int program;
	ShaderSource();
	~ShaderSource();
};