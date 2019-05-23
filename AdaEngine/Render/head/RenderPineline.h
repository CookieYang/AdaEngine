#pragma once
#include "RenderPass.h"
#include <vector>
class RenderPineline {
	enum PinelineType
	{
		FORWARD,
		DEFER,
		CARTOON
	};
	PinelineType pineline;
	std::vector<RenderPass> renderPasses;
public:
	RenderPineline();
	virtual ~RenderPineline() {};
	virtual void Draw();
	virtual void AddRenderPass(int index);
};