#pragma once
#include "AdaMath.h"
class SceneNode;
class MoveComponent {
public:
	MoveComponent(SceneNode* p);
	float speed;
	float sensitivity;
	void MoveForward(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveUp(float deltaTime);
	void AddYaw(float offset);
	void AddPitch(float offset);
	void AddRoll(float offset);
private:
	float yaw;
	float pitch;
	float roll;
	SceneNode * parent;
};