#include "SceneMesh.h"
#include "IRenderInterface.h"
#include "MeshComponent.h"

SceneMesh::SceneMesh() {
	mesh = new MeshComponent;
}

SceneMesh::~SceneMesh() {
	delete mesh;
}

void SceneMesh::setMesh(const std::string& name) {
	mesh->setMesh(name);
}

void SceneMesh::setGeometry(const std::string& name) {
	mesh->setGeometry(name);
}

void SceneMesh::setMaterial(const std::string& name) {
	mesh->setMaterial(name);
}

void SceneMesh::setMaterialForSection(const std::string& name, int sectionIndex) {
	mesh->setMaterialForSection(name, sectionIndex);
}

int SceneMesh::getSectionNum() {
	return mesh->getSectionNum();
}

void SceneMesh::doRun() {
	
}

void SceneMesh::doUpdateTransform() {
	mesh->updateTransform(transComponent.GetTransform().toGLM());
}

void init_SceneMesh(pybind11::module& m) {
	pybind11::class_<SceneMesh, SceneRenderable, PySceneRenderable<SceneMesh>>(m, "SceneMesh")
		.def(pybind11::init<>())
		.def("setGeometry", &SceneMesh::setGeometry)
		.def("setMesh", &SceneMesh::setMesh)
		.def("setMaterial", &SceneMesh::setMaterial)
		.def("setMaterialForSection", &SceneMesh::setMaterialForSection)
		.def("getSectionNum", &SceneMesh::getSectionNum)
		;
}