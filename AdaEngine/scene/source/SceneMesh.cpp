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
	Material* m = (Material*)RenderInterface::getSingleton()->GetResourceByName(name, GPUResource::GResourceType::MATRERIAL);
	m->attachToMeshSection(renderMesh->getMeshSection(sectionIndex));
}

MaterialInstance* SceneMesh::getMaterialInstanceForSection(int sectionIndex) {
	return renderMesh->getMatreialInstanceForSection(sectionIndex);
}

int SceneMesh::getSectionNum() {
	return renderMesh->getSectionNum();
}

void SceneMesh::Run() {
	SceneRenderable::Run();
}
