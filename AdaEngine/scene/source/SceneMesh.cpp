#include "SceneMesh.h"
#include "IRenderInterface.h"

SceneMesh::SceneMesh() {
	
}

SceneMesh::~SceneMesh() {

}

void SceneMesh::setMesh(const std::string& name) {
	mesh.setMesh(name);
}

void SceneMesh::setGeometry(const std::string& name) {
	mesh.setGeometry(name);
}

void SceneMesh::setMaterial(const std::string& name) {
	mesh.setMaterial(name);
}

void SceneMesh::setMaterialForSection(const std::string& name, int sectionIndex) {
	mesh.setMaterialForSection(name, sectionIndex);
}

int SceneMesh::getSectionNum() {
	return mesh.getSectionNum();
}

void SceneMesh::Run() {
	SceneRenderable::Run();
}

void SceneMesh::updateTransform() {
	mesh.updateTransform(transComponent.GetTransform());
}
