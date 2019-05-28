#include "ShaderSource.h"
#include "ResourceManager.h"

ShaderSource::ShaderSource():program(0),dirty(true) {

}

ShaderSource::~ShaderSource() {

}

void ShaderSource::setShaderData(const std::string& name) {
	ShaderData* sData = (ShaderData*)ResourceManager::singleton()->GetResourceByName(name);
	mShaderData = RefCountedPtr<ShaderData>(sData);
}

ShaderData* ShaderSource::getShaderData() {
	return mShaderData.get();
}

bool ShaderSource::getDirty() {
	return dirty;
}

void ShaderSource::setDirty(bool d) {
	dirty = d;
}