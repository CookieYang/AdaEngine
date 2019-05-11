#include "SceneNode.h"
#include "Engine.h"
void SceneNode::AttachToParent(std::shared_ptr<SceneNode>& parent) {
	weak_parent = std::weak_ptr<SceneNode>(parent);
	parent->AddChildren(std::shared_ptr<SceneNode>(this));
}

void SceneNode::AddChildren(const std::shared_ptr<SceneNode>& child) {
	childrens.push_back(child);
}

void SceneNode::AttachToRoot() {

}

glm::mat4 SceneNode::GetTransform() {
	return transform;
}

glm::vec3 SceneNode::GetPosition() {
	return position;
}

glm::vec3 SceneNode::GetScale() {
	return scale;
}

glm::vec3 SceneNode::GetRotation() {
	return rotation;
}

void SceneNode::SetTransform(glm::mat4 newTransform) {
	transform = newTransform;
}

void SceneNode::SetPosition(glm::vec3 newPosition) {
	position = newPosition;
}

void SceneNode::SetScale(glm::vec3 newScale) {
	scale = newScale;
}

void SceneNode::SetRotation(glm::vec3 newRotation) {
	rotation = newRotation;
}