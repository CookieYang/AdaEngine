#include "RenderPass.h"
#include "IRenderInterface.h"
#include <GL/glew.h>

void RenderPass::passBegin() {
	// call in rendering thread!!!
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void RenderPass::passEnd() {

}

void RenderPass::addMaterial(Material* material) {
	if (std::find(activeMaterials.begin(), activeMaterials.end(), material) != activeMaterials.end()) {
		return;
	}
	activeMaterials.push_back(material);
}