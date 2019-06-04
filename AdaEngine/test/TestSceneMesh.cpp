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

	cube->setScale(DMath::makeVect(0.01, 0.01, 0.01));
	// add one pawn
	ScenePawn* pawn = new ScenePawn;

	pawn->AttachToRoot();

	pawn->ActiveControl();
}

void TestSceneMesh::doRun() {
	double time = Engine::getInstance()->win->GetCurrentTime();
	//cube->setRotatation(DMath::makeVect(time * 5.0f, 0.0, 0.0));
}