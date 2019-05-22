#include "TestSceneMesh.h"
#include "SceneMesh.h"
#include "ResourceManager.h"
#include "DefaultRenderPass.h"

void TestSceneMesh::doInit() {
	SceneMesh* cube = new SceneMesh;
	GeometryData* cubeGeometry = dynamic_cast<GeometryData*>(ResourceManager::singleton()->loadTestCube());
	cube->setGeometryData(cubeGeometry);
	cube->AttachToRoot();
}

void TestSceneMesh::doRun() {

}