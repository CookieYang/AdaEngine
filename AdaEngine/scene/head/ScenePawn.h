#pragma once
#include "SceneRenderable.h"

class CameraComponent;
class MoveComponent;

class ScenePawn : public SceneRenderable { 
public:
	ScenePawn();
	virtual ~ScenePawn();
	void ActiveControl();
protected:
	CameraComponent* cameraCom;
	MoveComponent* moveCom;
private:
	void MoveForward(Event* event);
	void MoveBack(Event* event);
	void MoveRight(Event* event);
	void MoveLeft(Event* event);
	void TurnRight(Event* event);
	void TurnUp(Event* event);
	void Zoom(Event* event);
};

void init_ScenePawn(pybind11::module& m);