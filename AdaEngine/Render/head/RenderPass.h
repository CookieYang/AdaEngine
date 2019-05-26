#pragma once
#include <vector>

class Material;
class RenderPass {
	std::vector<Material*> activeMaterials;
public:
	RenderPass() {};
	virtual ~RenderPass() {};
	std::string passName;
	void Draw();
	void addMaterial(Material* material);
	void removeMaterial(Material* material) {};
};