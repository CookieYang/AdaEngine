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

void SceneNode::Scale(DVector3 scale) {
	transComponent.SetScale(scale.toVec3());
}

void SceneNode::Rotate(DVector3 rotation) {
	transComponent.SetRotation(rotation.toVec3());
}

void SceneNode::Translate(DVector3 translate) {
	transComponent.SetTranslate(translate.toVec3() + transComponent.GetPosition());
}

bool SceneNode::ProcessEvent(Event* event) {
	for (auto child : childrens) {
		if (child->ProcessEvent(event)) {
			event->bProcced = true;
		}
	}
	if (!event->bProcced) {
		if (event->getType() == EVENTYPE::KEYEVENT)
		{
			if (ProcessKeyEvent(event)) {
				event->bProcced = true;
			}
		}
		else if (event->getType() == EVENTYPE::MOUSEMOVEEVENT) {
			if (ProcessMouseMoveEvent(event)) {
				event->bProcced = true;
			}
		}
		else if (event->getType() == EVENTYPE::SCROLLEVENT) {
			if (ProcessScrollEvent(event)) {
				event->bProcced = true;
			}
		}
	}
	return false;
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
