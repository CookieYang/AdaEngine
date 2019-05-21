#include "SceneTree.h"
#include "SceneNode.h"

void SceneTree::Init() {

}

void SceneTree::ergodic(SceneNode* node) {
	node->Run();
	for (size_t i = 0; i < node->childrens.size(); i++)
	{
		SceneNode* child = node->childrens[i].get();
		child->Run();
	}
}

void SceneTree::Run() {
	ergodic(root.get());
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