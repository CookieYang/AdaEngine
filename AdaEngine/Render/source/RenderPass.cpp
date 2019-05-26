#include "RenderPass.h"
#include "IRenderInterface.h"

void RenderPass::Draw() {
      // renderInterface draw
	RenderInterface::getSingleton()->passDraw(this);
}

void RenderPass::addMaterial(Material* material) {
	activeMaterials.push_back(material);
}