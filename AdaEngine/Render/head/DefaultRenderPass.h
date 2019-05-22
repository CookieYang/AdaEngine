#pragma once
#include "RenderPass.h"
class DefalutRenderPass: public RenderPass {
public:
	DefalutRenderPass() {};
	~DefalutRenderPass() {};
	void setSectionNum(int n);
};