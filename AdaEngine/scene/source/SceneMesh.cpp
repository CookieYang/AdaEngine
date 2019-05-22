#include "SceneMesh.h"

SceneMesh::SceneMesh() {
	renderMesh = RefCountedPtr<MeshSource>(new MeshSource);
}

SceneMesh::~SceneMesh() {

}

void SceneMesh::setGeometryData(GeometryData* gData) {
	size_t length = gData->sectionsData.size();
	renderMesh->vaos.resize(length, 0);
	renderMesh->vbos.resize(length, 0);
	renderMesh->ebos.resize(length, 0);
	renderMesh->setGeometry(gData);
}

void SceneMesh::CreateRenderResource() {

}

void SceneMesh::Run() {
	SceneRenderable::Run();
}