#include "MoveComponent.h"
#include "SceneNode.h"

MoveComponent::MoveComponent(SceneNode* p):parent(p) {
	speed = 1.0f;
	sensitivity = 0.1f;
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;
}

void MoveComponent::MoveForward(float deltaTime) {
	float offset = speed * deltaTime;
	parent->transComponent.Translate(DMath::Normalized(-parent->transComponent.GetTransform().v.dir) * offset);
}

void MoveComponent::MoveRight(float deltaTime) {
	float offset = speed * deltaTime;
	parent->transComponent.Translate(DMath::Normalized(parent->transComponent.GetTransform().v.right) * offset);
}

void MoveComponent::MoveUp(float deltaTime) {
	float offset = speed * deltaTime;
	parent->transComponent.Translate(DMath::Normalized(parent->transComponent.GetTransform().v.up) * offset);
}

void MoveComponent::AddYaw(float offset) {
	yaw += offset * sensitivity;
	if (yaw > 85.0f)
		yaw = 85.0f;
	if (yaw < -85.0f)
		yaw = -85.0f;
	parent->transComponent.setRotation(DMath::makeVect(yaw, pitch, roll));
}

void MoveComponent::AddPitch(float offset) {
	 pitch += offset * sensitivity;
	parent->transComponent.setRotation(DMath::makeVect(yaw, pitch, roll));
}

void MoveComponent::AddRoll(float offset) {
	roll += offset * sensitivity;
	parent->transComponent.setRotation(DMath::makeVect(yaw, pitch, roll));
}
