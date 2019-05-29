#pragma once
#include "Application.h"
#include "SceneMesh.h"

class TestSceneMesh : public Application {
public:
	virtual void doRun() override;

	virtual void doInit() override;

private:
	SceneMesh* cube;
};