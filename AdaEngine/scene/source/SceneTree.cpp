#include "SceneTree.h"
#include "SceneNode.h"

void SceneTree::Init() {

}

void SceneTree::Run() {

}

void SceneTree::Destory() {
	
}

void SceneTree::AddNode(boost::shared_ptr<SceneNode>& node) {
	node->AttachToParent(root);
}

SceneTree::SceneTree() {

}

SceneTree::~SceneTree() {
	Destory();
}