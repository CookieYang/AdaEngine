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

void SceneNode::Scale(Vector3 scale) {
	transComponent.SetScale(scale.toVec3());
}

void SceneNode::Rotate(Vector3 rotation) {
	transComponent.SetRotation(rotation.toVec3());
}

void SceneNode::Translate(Vector3 translate) {
	transComponent.SetTranslate(translate.toVec3() + transComponent.GetPosition());
}
