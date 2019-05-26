#include "TestSceneMesh.h"
#include "SceneMesh.h"
#include "IRenderInterface.h"
#include "ResourceManager.h"

void TestSceneMesh::doInit() {

	SceneMesh* cube = new SceneMesh();
	// set Mesh 
	cube->setMesh("cube_mesh");

	// set Material
	cube->setMaterial("defalut_mat_ins");

	cube->AttachToRoot();
}

void TestSceneMesh::doRun() {

}