#include "SceneMesh.h"

SceneMesh::SceneMesh() {
	
}

SceneMesh::SceneMesh(MeshSource* mesh) {
	renderMesh = RefCountedPtr<MeshSource>(mesh);
}

SceneMesh::~SceneMesh() {

}

void SceneMesh::Run() {
	SceneRenderable::Run();
}
