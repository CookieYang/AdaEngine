#include "ForwardPineline.h"
#include "Material.h"

ForwardPineline::ForwardPineline() {
	RenderPass pass;
	pass.passName = "MeshPass";
	passes.push_back(pass);
}

void ForwardPineline::addMaterialToPass(Material* mat) {
	for (size_t i = 0; i < passes.size(); i++)
	{
		RenderPass pass = passes[i];
		if (pass.passName == mat->passName)
		{
			pass.addMaterial(mat);
		}
	}
}

void ForwardPineline::Draw() {
	for (size_t i = 0; i < passes.size(); i++)
	{
		RenderPass pass = passes[i];
		pass.Draw();
	}
}