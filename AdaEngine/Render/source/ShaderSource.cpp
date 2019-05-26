#include "ShaderSource.h"
#include "ResourceManager.h"

ShaderSource::ShaderSource():program(0),dirty(0) {

}

ShaderSource::~ShaderSource() {

}

void ShaderSource::setShaderData(const std::string& name) {
	ShaderData* sData = (ShaderData*)ResourceManager::singleton()->GetResourceByName(name);
	mShaderData = RefCountedPtr<ShaderData>(sData);
	shaderIDs.resize(sData->shaderStrs.size(), 0);
}