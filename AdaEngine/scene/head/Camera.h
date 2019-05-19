#pragma once
#include "SceneNode.h"

class Camera : public SceneNode {
public:
	glm::mat4 viewMatrix;
private:
	glm::vec3 forwardDirection;
	glm::vec3 upDirection;
	float farPlane;
	float nearPlane;
	float fov;
	bool bActive;
};