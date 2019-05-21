#include "SceneNode.h"
#include "Engine.h"
#include "SceneTree.h"
void SceneNode::AttachToParent(SceneNode* parent) {
	if (parent)
	{
		weak_parent = parent;
		parent->AddChildren(this);
	}
}

void SceneNode::AddChildren(SceneNode* child) {
	childrens.push_back(RefCountedPtr<SceneNode>(child));
}

void SceneNode::AttachToRoot() {
	Engine::getInstance()->sceneTree->AddNode(this);
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