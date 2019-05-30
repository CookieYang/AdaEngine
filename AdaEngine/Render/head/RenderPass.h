#pragma once
#include <vector>

class Material;
class RenderPass {
public:
	unsigned long passMask = 1;
	std::vector<Material*> activeMaterials;
	RenderPass() {};
	virtual ~RenderPass() {};
	virtual void passBegin();
	virtual void passEnd();
	void addMaterial(Material* material);
	void removeMaterial(Material* material) {};
	double currentTime;
};