#include "TestSceneMesh.h"
#include "SceneMesh.h"
#include "ResourceManager.h"
#include "DefaultRenderPass.h"

void TestSceneMesh::doInit() {
	SceneMesh* cube = new SceneMesh;

	//cube->setGeometryData(cubeGeometry);
	cube->AttachToRoot();
}

void TestSceneMesh::doRun() {

}