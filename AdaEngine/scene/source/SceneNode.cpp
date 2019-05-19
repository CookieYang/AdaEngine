#include "SceneNode.h"
#include "Engine.h"
void SceneNode::AttachToParent(RefCountedPtr<SceneNode>& parent) {
	if (parent.isValid())
	{
		weak_parent = parent.get();
		parent->AddChildren(RefCountedPtr<SceneNode>(this));
	}
}

void SceneNode::AddChildren(const RefCountedPtr<SceneNode>& child) {
	childrens.push_back(child);
}

void SceneNode::AttachToRoot() {

}

SceneNodeType SceneNode::getNodeType() {
	return type;
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