#include "DefaultRenderPass.h"
#include "DefalutMaterial.h"
#include "ResourceManager.h"

void DefalutRenderPass::setSectionNum(int n) {
	//Material* dMaterial = ResourceManager::singleton()->loadDefalutMaterial();
	for (size_t i = 0; i < n; i++)
	{
		//materials.push_back(RefCountedPtr<Material>(dMaterial));
	}
}
