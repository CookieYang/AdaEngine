#include "MoveComponent.h"
#include "SceneNode.h"
#include "Engine.h"

MoveComponent::MoveComponent(SceneNode* p):parent(p) {
	speed = 2.5f;
	sensitivity = 0.1f;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

void MoveComponent::MoveForward(float cof) {
	double currentTime = Engine::getInstance()->win->GetCurrentTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
	float velocity = speed * deltaTime * cof;
	parent->transComponent.SetTranslate(velocity * GetForward(parent->transComponent.GetTransform()));
}

void MoveComponent::MoveRight(float cof) {
	double currentTime = Engine::getInstance()->win->GetCurrentTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
	float velocity = speed * deltaTime* cof;
	parent->transComponent.SetTranslate(velocity * GetRight(parent->transComponent.GetTransform()));
}

void MoveComponent::MoveUp(float cof) {
	double currentTime = Engine::getInstance()->win->GetCurrentTime();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
	float velocity = speed * deltaTime* cof;
	parent->transComponent.SetTranslate(velocity * GetUP(parent->transComponent.GetTransform()));
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
