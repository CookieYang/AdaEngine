#include "TestSceneMesh.h"
#include "Engine.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

void TestSceneMesh::doInit() {

	cube = new SceneMesh();
	// set Mesh 
	cube->setMesh("cube_mesh");

	// set Material
	cube->setMaterial("defalut_mat_ins");

	cube->AttachToRoot();
}

void TestSceneMesh::doRun() {
	double time = Engine::getInstance()->win->GetCurrentTime();
	cube->Scale(Vector3(0.01, 0.01, 0.01));
	cube->Rotate(Vector3((float)time * 20.0f, (float)time * 20.0f, (float)time * 20.0f));
}