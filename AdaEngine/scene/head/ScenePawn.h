#pragma once
#include "SceneRenderable.h"

class CameraComponent;
class MoveComponent;

class ScenePawn : public SceneRenderable { 
public:
	ScenePawn();
	virtual ~ScenePawn() {};
	void ActiveControl();
protected:
	CameraComponent* cameraCom;
	MoveComponent* moveCom;
	virtual bool ProcessKeyEvent(Event* kEvent) override;
	virtual bool ProcessMouseMoveEvent(Event* mEvent) override;
	virtual bool ProcessScrollEvent(Event* sEvent) override;
private:
	float deltaTime;
	float lastFrame;
	DMath::vec_t lastMousePos;
	bool bFirstMouse;
};

void init_ScenePawn(pybind11::module& m);