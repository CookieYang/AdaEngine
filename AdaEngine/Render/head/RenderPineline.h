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
	virtual void Draw() = 0;
	virtual void addRenderPass(std::string name)  = 0;
	virtual void addMaterialToPass(Material* mat)  = 0;
	virtual void removeMaterialFromPass(std::string name)  = 0;
	static RenderPineline* createPineline(PinelineType type);
};