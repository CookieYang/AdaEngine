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

void SceneNode::Scale(DVector3<float> scale) {
	transComponent.SetScale(scale.toVec3());
}

void SceneNode::Rotate(DVector3<float> rotation) {
	transComponent.SetRotation(rotation.toVec3());
}

void SceneNode::Translate(DVector3<float> translate) {
	transComponent.SetTranslate(translate.toVec3() + transComponent.GetPosition());
}

void SceneNode::ProcessEvent(Event* event) {
	for (auto child : childrens) {
		child->ProcessEvent(event);
	}
	if (!event->bProcced) {
		if (event->getType() == EVENTYPE::KEYEVENT)
		{
			ProcessKeyEvent(event);
		}
		else if (event->getType() == EVENTYPE::MOUSEMOVEEVENT) {
			ProcessMouseMoveEvent(event);
		}
		else if (event->getType() == EVENTYPE::SCROLLEVENT) {
			ProcessScrollEvent(event);
		}
		event->bProcced = true;
	}
}

void SceneNode::Run() {
	doRun();
	for (auto child : childrens) {
		child->Run();
	}
}

void SceneNode::updateTransform() {
	doUpdateTransform();
	for (auto child : childrens) {
		child->updateTransform();
	}
}
