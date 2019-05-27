#pragma once
#include <vector>

class Material;
class RenderPass {
public:
	std::vector<Material*> activeMaterials;
	RenderPass() {};
	virtual ~RenderPass() {};
	virtual void passBegin();
	virtual void passEnd();
	std::string passName;
	void addMaterial(Material* material);
	void removeMaterial(Material* material) {};
	double currentTime;
};