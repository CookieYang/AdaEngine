#include "TestSceneMesh.h"
#include "Engine.h"
#include "AdaMath.h"
#include "ScenePawn.h"


void TestSceneMesh::doInit() {

	cube = new SceneMesh;
	// set Mesh 
	cube->setMesh("cube_mesh");

	// set Material
	cube->setMaterial("defalut_mat_ins");

	cube->AttachToRoot();

	// add one pawn
	ScenePawn* pawn = new ScenePawn;

	pawn->AttachToRoot();
}

void TestSceneMesh::doRun() {
	double time = Engine::getInstance()->win->GetCurrentTime();
	cube->Scale(DVector3<float>(0.01, 0.01, 0.01));
	cube->Rotate(DVector3<float>((float)time * 20.0f, (float)time * 20.0f, (float)time * 20.0f));
}