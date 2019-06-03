#pragma once
#include "AdaMath.h"
class SceneNode;
class MoveComponent {
public:
	MoveComponent(SceneNode* p);
	float speed;
	float sensitivity;
	void MoveForward(float cof);
	void MoveRight(float cof);
	void MoveUp(float cof);
	void AddYaw(float offset);
	void AddPitch(float offset);
	void AddRoll(float offset);
private:
	float deltaTime ; 
	float lastFrame ; 
	SceneNode * parent;
};