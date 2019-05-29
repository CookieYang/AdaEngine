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
	glm::mat4 trans(1.0f);
	trans = glm::scale(trans, glm::vec3(0.01, 0.01, 0.01));
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)time * 0.8f, glm::vec3(1.0f, 1.0f, 1.0f));
	cube->SetTransform(trans);
}