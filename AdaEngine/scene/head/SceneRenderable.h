#pragma once
#include "SceneNode.h"
#include "RenderPass.h"

class SceneRenderable : public SceneNode {
public:
	SceneRenderable() {};
	virtual ~SceneRenderable() {};
	virtual void CreateRenderResource() {};
	virtual void Run() override;
};