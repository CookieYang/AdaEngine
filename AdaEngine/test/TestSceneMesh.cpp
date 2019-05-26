#include "TestSceneMesh.h"
#include "SceneMesh.h"
#include "IRenderInterface.h"
#include "ResourceManager.h"

void TestSceneMesh::doInit() {

	SceneMesh* cube = new SceneMesh();
	// set Mesh 
	cube->setMesh("cube_mesh");
	cube->setGeometry("cube_mesh_c");
	// set Material
	cube->setMaterial("defalut_mat");
	// set MaterialInstance
	MaterialInstance* matInstance = cube->getMaterialInstanceForSection(0);
	matInstance->attachTexture("defalut_tex");

	cube->AttachToRoot();
}

void TestSceneMesh::doRun() {

}