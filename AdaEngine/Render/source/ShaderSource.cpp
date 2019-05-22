#include "ShaderSource.h"

ShaderSource::ShaderSource():program(0) {

}

void ShaderSource::setShaderData(ShaderData* shaderData) {
	mShaderData = RefCountedPtr<ShaderData>(shaderData);
	shaderIDs.resize(shaderData->shaderStrs.size(), 0);
}