#include "MoveComponent.h"
#include "SceneNode.h"
#include "Engine.h"

MoveComponent::MoveComponent(SceneNode* p):parent(p) {
	speed = 2.5f;
	sensitivity = 0.1f;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;
}

void MoveComponent::MoveForward(float cof) {
	double currentTime = Engine::getInstance()->win->GetCurrentTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
	float velocity = speed * deltaTime * cof;
	parent->transComponent.Translate(parent->transComponent.GetTransform().v.dir * velocity);
}

void MoveComponent::MoveRight(float cof) {
	double currentTime = Engine::getInstance()->win->GetCurrentTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
	float velocity = speed * deltaTime* cof;
	parent->transComponent.Translate(parent->transComponent.GetTransform().v.right * velocity);
}

void MoveComponent::MoveUp(float cof) {
	double currentTime = Engine::getInstance()->win->GetCurrentTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
	float velocity = speed * deltaTime* cof;
	parent->transComponent.Translate(parent->transComponent.GetTransform().v.up * velocity);
}

void MoveComponent::AddYaw(float offset) {
	yaw = offset * sensitivity;
	parent->transComponent.RotateAxis(yaw, parent->transComponent.GetTransform().v.up);
}

void MoveComponent::AddPitch(float offset) {
	 pitch = offset * sensitivity;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	parent->transComponent.RotateAxis(pitch, parent->transComponent.GetTransform().v.right);
}

void MoveComponent::AddRoll(float offset) {
	roll = offset * sensitivity;
	parent->transComponent.RotateAxis(roll, parent->transComponent.GetTransform().v.dir);
}
