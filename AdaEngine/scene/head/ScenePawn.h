#pragma once
#include "SceneNode.h"

class CameraComponent;
class MoveComponent;

class ScenePawn : public SceneNode { 
public:
	ScenePawn();
	virtual ~ScenePawn() {};
	virtual void ActiveControl();
protected:
	CameraComponent* cameraCom;
	MoveComponent* moveCom;
	virtual bool ProcessKeyEvent(Event* kEvent) override;
	virtual bool ProcessMouseMoveEvent(Event* mEvent) override;
	virtual bool ProcessScrollEvent(Event* sEvent) override;
private:
	DVector2 lastMousePos;
	bool bFirstMouse;
};