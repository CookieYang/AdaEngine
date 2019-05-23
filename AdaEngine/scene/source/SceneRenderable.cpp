#include "SceneRenderable.h"

void SceneRenderable::Run() {

}

void SceneRenderable::AttachToRoot() {
	CreateRenderResource();
	SceneNode::AttachToRoot();
}
