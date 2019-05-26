#pragma once
#include "RenderPass.h"
#include <vector>
enum PinelineType
{
	FORWARD,
	DEFER,
	CARTOON
};
class RenderPineline {
public:
	std::vector<RenderPass> passes;
	virtual void Draw() {};
	virtual void addRenderPass(std::string name) {};
	virtual void addMaterialToPass(Material* mat) {};
	virtual void removeMaterialFromPass(std::string name) {};
	static RenderPineline* createPineline(PinelineType type);
};