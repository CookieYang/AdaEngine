#include "SceneTree.h"
#include "SceneNode.h"

void SceneTree::Init() {

}

void SceneTree::Run() {
	root->Run();
	root->updateTransform();
}

void SceneTree::ProcessEvent(Event* event, bool bMouseEnable) {
	if (bMouseEnable)
	{
		root->ProcessEvent(event);
	}
	delete event;
}

void SceneTree::Destory() {

}

void SceneTree::AddNode(SceneNode* node) {
	node->AttachToParent(root.get());
}

SceneTree::SceneTree() {
	root = RefCountedPtr<SceneNode>(new SceneNode);
}

SceneTree::~SceneTree() {
	Destory();
}