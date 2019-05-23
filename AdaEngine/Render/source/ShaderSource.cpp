#include "ShaderSource.h"

ShaderSource::ShaderSource():program(0) {

}

ShaderSource::ShaderSource(ShaderData* shaderData) {
	mShaderData = RefCountedPtr<ShaderData>(shaderData);
	shaderIDs.resize(shaderData->shaderStrs.size(), 0);
	// upload to gpu
}

ShaderSource::~ShaderSource() {

}

void ShaderSource::setShaderData(ShaderData* shaderData) {

}