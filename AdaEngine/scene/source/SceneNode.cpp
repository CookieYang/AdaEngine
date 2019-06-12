#include "SceneNode.h"
#include "Engine.h"
#include "SceneTree.h"
#include "InputComponent.h"
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
	for (auto component : components) {
		InputComponent* com = dynamic_cast<InputComponent*>(component.get());
		if (com)
		{
			if (com->ProcessEvent(event))
			{
				event->bProcced = true;
			}
			break;
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

void init_SceneNode(pybind11::module& m) {
	pybind11::class_<SceneNode, PySceneNode<>>(m, "SceneNode")
		.def("MakeNode", []() { return new SceneNode; }, pybind11::return_value_policy::reference)
		.def("AttachToRoot", &SceneNode::AttachToRoot)
		.def("AttachToParent", &SceneNode::AttachToParent)
		.def("setScale", &SceneNode::setScale)
		.def("setRotatation", &SceneNode::setRotatation)
		.def("setPosition", &SceneNode::setPosition)
		.def("Run", &SceneNode::Run)
		.def("updateTransform", &SceneNode::updateTransform)
		;
}
