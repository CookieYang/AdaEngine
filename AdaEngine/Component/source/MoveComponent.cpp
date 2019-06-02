#include "MoveComponent.h"
#include "SceneNode.h"
#include "Engine.h"

MoveComponent::MoveComponent(SceneNode* p):parent(p) {
	speed = 2.5f;
	sensitivity = 0.1f;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

void MoveComponent::MoveForward() {
	double currentTime = Engine::getInstance()->win->GetCurrentTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
	float velocity = speed * deltaTime;
//	parent->transComponent.SetTranslate(velocity * parent->transComponent.GetForward());
}

void MoveComponent::MoveRight() {
	double currentTime = Engine::getInstance()->win->GetCurrentTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
	float velocity = speed * deltaTime;
//	parent->transComponent.SetTranslate(velocity * parent->transComponent.GetRight());
}

void MoveComponent::MoveUp() {
	double currentTime = Engine::getInstance()->win->GetCurrentTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
	float velocity = speed * deltaTime;
//	parent->transComponent.SetTranslate(velocity * parent->transComponent.GetUP());
}

void MoveComponent::AddYaw(float offset) {
	float yaw = offset * sensitivity;
	parent->transComponent.SetRotation(glm::vec3(0.0, yaw, 0.0) + parent->transComponent.GetRotation());
}

void MoveComponent::AddPitch(float offset) {
	float pitch = offset * sensitivity;
	parent->transComponent.SetRotation(glm::vec3(pitch, 0.0, 0.0) + parent->transComponent.GetRotation());
}

void MoveComponent::AddRoll(float offset) {
	float roll = offset * sensitivity;
	parent->transComponent.SetRotation(glm::vec3(0.0, 0.0, roll) + parent->transComponent.GetRotation());
}
