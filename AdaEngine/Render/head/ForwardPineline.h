#pragma once
#include "RenderPineline.h"

class ForwardPineline : public RenderPineline {
public:
	ForwardPineline();
	~ForwardPineline() {};
	virtual void addRenderPass(std::string name) override {};
	virtual void addMaterialToPass(Material* mat) override;
	virtual void removeMaterialFromPass(std::string name) override {};
};