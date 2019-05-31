#include "TransformComponent.h"

glm::mat4 TransformComponent::GetTransform() {
	return transform;
}

glm::vec3 TransformComponent::GetPosition() {
	return position;
}

glm::vec3 TransformComponent::GetScale() {
	return scale;
}

glm::vec3 TransformComponent::GetRotation() {
	return glm::eulerAngles(rotation);
}

void TransformComponent::SetTransform(glm::mat4 newTransform) {
	transform = newTransform;
}

void TransformComponent::SetTranslate(glm::vec3 translate) {
	position += translate;
	glm::mat4 trans = glm::scale(glm::mat4(1.0f), scale);
	trans = glm::mat4_cast(rotation) * trans;
	transform =  glm::translate(trans, translate);
}

void TransformComponent::SetScale(glm::vec3 newScale) {
	scale = newScale;
	glm::mat4 trans = glm::scale(glm::mat4(1.0f), scale);
	trans = glm::mat4_cast(rotation) * trans;
	transform = glm::translate(trans, position);
}

void TransformComponent::SetRotation(glm::vec3 newRotation) {
	rotation = glm::qua<float>(glm::radians(newRotation));
	glm::mat4 trans = glm::scale(glm::mat4(1.0f), scale);
	trans = glm::mat4_cast(rotation) * trans;
	transform = glm::translate(trans, position);
}