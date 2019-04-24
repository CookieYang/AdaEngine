#include "SceneTree.h"

IMPLEMENT_CLASS(SceneTree)

bool SceneTree::Init() {
	context = new GLContext;
	return context->initContext();
}

void SceneTree::Run() {
	while (context->isContextValid())
	{
		context->swapBuffers();
		context->PollEvents();
	}

}

void SceneTree::Destory() {
	context->clearContext();
	delete context;
}

SceneTree::SceneTree() {

}

SceneTree::~SceneTree() {
	Destory();
}