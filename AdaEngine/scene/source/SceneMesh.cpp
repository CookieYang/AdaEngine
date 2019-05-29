#include "SceneMesh.h"
#include "IRenderInterface.h"

SceneMesh::SceneMesh() {
	
}

SceneMesh::~SceneMesh() {

}

void SceneMesh::setMesh(const std::string& name) {
	GPUResource* res = RenderInterface::getSingleton()->GetResourceByName(name, GPUResource::GResourceType::MESH);
	MeshSource* mesh = dynamic_cast<MeshSource*>(res);
	renderMesh = RefCountedPtr<MeshSource>(mesh);
}

void SceneMesh::setGeometry(const std::string& name) {
	renderMesh->setGeometry(name);
}

void SceneMesh::setMaterial(const std::string& name) {
	for (size_t i = 0; i < getSectionNum(); i++)
	{
		setMaterialForSection(name, i);
	}
}

void SceneMesh::setMaterialForSection(const std::string& name, int sectionIndex) {
	MaterialInstance* m = (MaterialInstance*)RenderInterface::getSingleton()->GetResourceByName(name, GPUResource::GResourceType::MATERIALINS);
	renderMesh->getMeshSection(sectionIndex)->attachMaterial(m);
}

int SceneMesh::getSectionNum() {
	return renderMesh->getSectionNum();
}

void SceneMesh::Run() {
	SceneRenderable::Run();
}

void SceneMesh::updateTransform(const glm::mat4& tran) {
	for (size_t i = 0; i < getSectionNum(); i++)
	{
		MeshSection* section = renderMesh->getMeshSection(i);
		MaterialVar var;
		var.mType = MaterialVar::VarType::MAT4;
		var.mVar.mat4 = tran;
		RenderInterface::getSingleton()->updateMaterialParam(section->mInstance.get(), "modelMat", var);
	}
}
