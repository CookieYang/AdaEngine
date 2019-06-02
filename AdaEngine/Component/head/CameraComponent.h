#pragma once
#include "AdaMath.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class SceneNode;
class TransformComponent;
class CameraComponent {
public:
	TransformComponent* trans;
	// Camera options
	float Zoom;
	CameraComponent(SceneNode* parent);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
private:
	SceneNode* parent;
};