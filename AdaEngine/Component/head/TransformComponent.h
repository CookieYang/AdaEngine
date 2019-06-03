#pragma once
#include "AdaMath.h"
class TransformComponent {
public:
	TransformComponent();
	glm::mat4 GetTransform();
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();
	void SetTransform(glm::mat4 newTransform);
	void SetTranslate(glm::vec3 translate);
	void SetScale(glm::vec3 newScale);
	void SetRotation(glm::vec3 newRotation);
private:
	glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 scale;
	glm::qua<float> rotation;
};