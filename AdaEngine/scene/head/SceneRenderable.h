#pragma once
#include "SceneNode.h"

class SceneRenderable : public SceneNode {
public:
	SceneRenderable(): renderReady(false) {};
	virtual ~SceneRenderable() {};
	virtual void CreateRenderResource() {};
	bool getRenderReady() { return renderReady; };
	void setRenderReady(bool ready) { renderReady = ready; };
	virtual void Run() override;
	virtual void AttachToRoot() override;
protected:
	volatile bool renderReady;  // read only (will be set true when ready to render) 
};