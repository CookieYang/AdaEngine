#include "SceneRenderable.h"

void SceneRenderable::Run() {
	if (!renderReady)
	{
		return;
	}
}

void SceneRenderable::AttachToRoot() {
	SceneNode::AttachToRoot();
	CreateRenderResource();
}