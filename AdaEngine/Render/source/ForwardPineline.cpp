#include "ForwardPineline.h"
#include "Material.h"

ForwardPineline::ForwardPineline() {
	RenderPass pass;
	pass.passMask = pass.passMask << 1;
	passes.push_back(pass);
}

void ForwardPineline::addMaterialToPass(Material* mat) {
	for (size_t i = 0; i < passes.size(); i++)
	{
		RenderPass* pass = &passes[i];
		pass->addMaterial(mat);
	}
}