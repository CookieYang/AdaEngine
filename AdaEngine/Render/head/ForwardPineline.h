#pragma once
#include "RenderPineline.h"

class ForwardPineline : public RenderPineline {
	std::vector<RenderPass> passes;
public:
	ForwardPineline();
	~ForwardPineline() {};
	virtual void Draw() override;
	virtual void addRenderPass(std::string name) override {};
	virtual void addMaterialToPass(Material* mat) override;
	virtual void removeMaterialFromPass(std::string name) override {};
};