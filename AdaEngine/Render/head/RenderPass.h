#pragma once
#include <vector>

class Material;
class RenderPass {
public:
	std::vector<Material*> activeMaterials;
	RenderPass() {};
	virtual ~RenderPass() {};
	std::string passName;
	void Draw();
	void addMaterial(Material* material);
	void removeMaterial(Material* material) {};
	double currentTime;
};