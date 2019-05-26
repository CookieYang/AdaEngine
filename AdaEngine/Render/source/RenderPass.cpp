#include "RenderPass.h"
#include "IRenderInterface.h"

void RenderPass::Draw() {
      // renderInterface draw
	/*RenderInterface::getSingleton()->passDraw(this);*/
}

void RenderPass::addMaterial(Material* material) {
	if (std::find(activeMaterials.begin(), activeMaterials.end(), material) != activeMaterials.end()) {
		return;
	}
	activeMaterials.push_back(material);
}