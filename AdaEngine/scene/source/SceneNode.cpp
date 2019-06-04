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

void SceneNode::setScale(DMath::vec_t s) {
	transComponent.setScale(s);
}

void SceneNode::setRotatation(DMath::vec_t rot) {
	transComponent.setRotation(rot);
}

void SceneNode::setPosition(DMath::vec_t pos) {
	transComponent.setPosition(pos);
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
