#include "MeshComponent.h"
#include "IRenderInterface.h"
#include "ResourceManager.h"

void MeshComponent::setMesh(const std::string& name) {
	GPUResource* res = ResourceManager::singleton()->GetResourceByName(name, GPUResource::GResourceType::MESH);
	MeshSource* mRes = dynamic_cast<MeshSource*>(res);
	sMesh = RefCountedPtr<MeshSource>(mRes);
	if (!mRes->loaded)
	{
		RenderInterface::getSingleton()->uploadGeometry(mRes);
		mRes->loaded = true;
	}
}

void MeshComponent::setGeometry(const std::string& name) {
	sMesh->setGeometry(name);
}

void MeshComponent::setMaterial(const std::string& name) {
	for (size_t i = 0; i < getSectionNum(); i++)
	{
		setMaterialForSection(name, i);
	}
}

void MeshComponent::setMaterialForSection(const std::string& name, int sectionIndex) {
	MaterialInstance* m = (MaterialInstance*)ResourceManager::singleton()->GetResourceByName(name, GPUResource::GResourceType::MATERIALINS);
	sMesh->getMeshSection(sectionIndex)->attachMaterial(m);
}

int MeshComponent::getSectionNum() {
	return sMesh->getSectionNum();
}

void MeshComponent::updateTransform(const glm::mat4& trans) {
	sMesh->setTransform(trans);
}