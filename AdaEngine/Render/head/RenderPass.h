#pragma once
#include "RefCountedPtr.h"
#include "Material.h"

class RenderPass {
protected:
	std::vector<RefCountedPtr<Material>> materials;
public:
	RenderPass() {};
	virtual ~RenderPass() {};
};