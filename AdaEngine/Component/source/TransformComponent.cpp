#include "TransformComponent.h"

TransformComponent::TransformComponent():
	transform(glm::mat4(1.0f)),
	rotation(glm::qua<float>(glm::radians(glm::vec3(0.0, 0.0, 0.0)))),
	scale(glm::vec3(1.0f, 1.0f, 1.0f)),
	position(glm::vec3(0.0f, 0.0f, 0.0f))
{
	
}

glm::vec3 TransformComponent::GetForward(const glm::mat4& mat) {
	return glm::vec3();
}

glm::vec3 TransformComponent::GetRight(const glm::mat4& mat) {
	return glm::vec3();
}

glm::vec3 TransformComponent::GetUP(const glm::mat4& mat) {
	return glm::vec3();
}

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