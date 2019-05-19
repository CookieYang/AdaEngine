#include "SceneTree.h"
#include "SceneNode.h"

void SceneTree::Init() {

}

void SceneTree::Run() {

}

void SceneTree::Destory() {
	
}

void SceneTree::AddNode(RefCountedPtr<SceneNode>& node) {
	node->AttachToParent(root);
}

SceneTree::SceneTree() {

}

SceneTree::~SceneTree() {
	Destory();
}