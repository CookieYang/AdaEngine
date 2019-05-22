#pragma once
#include "RawResource.h"
#include <string>
#include <vector>

class ShaderData : public RawResource {
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