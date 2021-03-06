#pragma once
#include "AdaMath.h"
#include "Component.h"

const float ZOOM = 45.0f;

class SceneNode;
class TransformComponent;
class CameraComponent: public Component {
public:
	TransformComponent* trans;
	void setActive();
	// Camera options
	float Zoom;
	CameraComponent(SceneNode* parent);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
private:
	SceneNode* parent;
};