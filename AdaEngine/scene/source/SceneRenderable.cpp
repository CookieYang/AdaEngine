#include "SceneRenderable.h"

void SceneRenderable::Run() {
	if (!renderReady)
	{
		return;
	}
}

void SceneRenderable::AttachToRoot() {
	CreateRenderResource();
	SceneNode::AttachToRoot();
}

void SceneRenderable::AddOnePass(const RenderPass& onePass) {
	pass.push_back(onePass);
}