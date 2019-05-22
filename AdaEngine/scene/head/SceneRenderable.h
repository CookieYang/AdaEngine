#pragma once
#include "SceneNode.h"
#include "RenderPass.h"

class SceneRenderable : public SceneNode {
public:
	SceneRenderable(): renderReady(false) {};
	virtual ~SceneRenderable() {};
	virtual void CreateRenderResource() {};
	bool getRenderReady() { return renderReady; };
	void setRenderReady(bool ready) { renderReady = ready; };
	virtual void Run() override;
	virtual void AttachToRoot() override;
	void AddOnePass(const RenderPass& onePass);
protected:
	volatile bool renderReady;  // read only (will be set true when ready to render) 
	std::vector<RenderPass> pass;
};