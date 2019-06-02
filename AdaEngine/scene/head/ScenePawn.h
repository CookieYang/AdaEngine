#pragma once
#include "SceneNode.h"

class CameraComponent;
class MoveComponent;

class ScenePawn : public SceneNode { 
public:
	ScenePawn();
	virtual ~ScenePawn() {};
protected:
	CameraComponent* cameraCom;
	MoveComponent* moveCom;
	virtual void ProcessKeyEvent(Event* kEvent) override {};
	virtual void ProcessMouseMoveEvent(Event* mEvent) override {};
	virtual void ProcessScrollEvent(Event* sEvent) override {};
};