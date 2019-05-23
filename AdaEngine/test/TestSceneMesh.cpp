#include "TestSceneMesh.h"
#include "SceneMesh.h"
#include "ResourceManager.h"
#include "DefaultRenderPass.h"

void TestSceneMesh::doInit() {
	MeshSource* mesh = dynamic_cast<MeshSource*>(ResourceManager::singleton()->searchResourceByName("test_cube_obj", GPUResource::GResourceType::MESH));
	SceneMesh* cube = new SceneMesh(mesh);
	cube->AttachToRoot();
}

void TestSceneMesh::doRun() {

}