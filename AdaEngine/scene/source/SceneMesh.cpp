#include "SceneMesh.h"
#include "DefaultRenderPass.h"

SceneMesh::SceneMesh() {
	renderMesh = RefCountedPtr<MeshSource>(new MeshSource);
}

SceneMesh::~SceneMesh() {

}

void SceneMesh::setGeometryData(GeometryData* gData) {
	renderMesh->setGeometry(gData);
}

void SceneMesh::CreateRenderResource() {
	// upload geometry data
	DefalutRenderPass dPass;
	AddOnePass(dPass);
}

void SceneMesh::Run() {
	SceneRenderable::Run();
}
