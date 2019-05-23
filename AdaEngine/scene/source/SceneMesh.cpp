#include "SceneMesh.h"
#include "DefaultRenderPass.h"

SceneMesh::SceneMesh() {
	
}

SceneMesh::SceneMesh(MeshSource* mesh) {
	renderMesh = RefCountedPtr<MeshSource>(mesh);
}

SceneMesh::~SceneMesh() {

}

void SceneMesh::setGeometryData(MeshSource* gData) {
	
}

void SceneMesh::CreateRenderResource() {
	DefalutRenderPass dPass;
	AddOnePass(dPass);
}

void SceneMesh::Run() {
	SceneRenderable::Run();
}
