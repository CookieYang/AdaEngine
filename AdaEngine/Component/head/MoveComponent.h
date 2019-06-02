#pragma once
#include "AdaMath.h"
class SceneNode;
class MoveComponent {
public:
	MoveComponent(SceneNode* p);
	float speed;
	float sensitivity;
	void MoveForward();
	void MoveRight();
	void MoveUp();
	void AddYaw(float offset);
	void AddPitch(float offset);
	void AddRoll(float offset);
private:
	float deltaTime ; 
	float lastFrame ; 
	SceneNode * parent;
};