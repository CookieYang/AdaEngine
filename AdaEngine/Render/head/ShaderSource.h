#pragma once
#include "RefCountedPtr.h"
#include "ShaderData.h"

class ShaderSource: public RefCountable {
	RefCountedPtr<ShaderData> mShaderData;
public:
	void setShaderData(ShaderData* shaderData);
	unsigned int program;
	std::vector<unsigned int> shaderIDs;
	ShaderSource();
	~ShaderSource() {};
};