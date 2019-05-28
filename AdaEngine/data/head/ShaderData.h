#pragma once
#include "CPUResource.h"
#include <string>
#include <vector>

class ShaderData : public CPUResource {
public:
	enum ShaderType
	{
		VERTEXSHADER,
		FRAGMENTSHADER,
		GEOMETRYSHADER
	};

	struct shaderString
	{
		ShaderType shaderType;
		std::string shaderStr;
	};

	std::vector<shaderString> shaderStrs;
};