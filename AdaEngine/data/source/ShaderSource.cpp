#include "ShaderSource.h"
#include "ResourceManager.h"

ShaderSource::ShaderSource(ShaderData* data):program(0),dirty(true) {
	mShaderData = RefCountedPtr<ShaderData>(data);
}

ShaderSource::~ShaderSource() {

}

void ShaderSource::setShaderData(const std::string& name) {
	//ShaderData* sData = (ShaderData*)ResourceManager::singleton()->GetResourceByName(name);
	//mShaderData = RefCountedPtr<ShaderData>(sData);
	//setResPath(sData->getResPath());
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