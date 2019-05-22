#include "SceneMesh.h"

SceneMesh::SceneMesh() {
	renderMesh = RefCountedPtr<MeshSource>(new MeshSource);
}

SceneMesh::~SceneMesh() {

}

void SceneMesh::setGeometryData(GeometryData* gData) {
	renderMesh->setGeometry(gData);
}

void SceneMesh::CreateRenderResource() {

}

void SceneMesh::Run() {
	SceneRenderable::Run();
}