#include "Material.h"
#include "MeshSource.h"
#include "IRenderInterface.h"
void Material::attachToMeshSection(MeshSection* meshSection) {
	if (meshRefs.size() == 0) {
		// add to render pass;
		RenderInterface::getSingleton()->addMaterialToPineline(this);
	}

	// create defalut material Instance
	meshSection->material = this;
	MaterialVar var1;
	var1.bindingName = "modelMat";
	var1.mType = MaterialVar::VarType::MAT4;
	var1.mVar.mat4 = glm::mat4(1.0f);

	MaterialVar var2;
	var2.bindingName = "viewMat";
	var2.mType = MaterialVar::VarType::MAT4;
	var2.mVar.mat4 = glm::mat4(1.0f);

	MaterialVar var3;
	var3.bindingName = "projMat";
	var3.mType = MaterialVar::VarType::MAT4;
	var3.mVar.mat4 = glm::mat4(1.0f);

	meshSection->mInstance.materialVars.push_back(var1);
	meshSection->mInstance.materialVars.push_back(var2);
	meshSection->mInstance.materialVars.push_back(var3);

	if (!meshSection->loaded)
	{
		// upload mesh to GPU
		RenderInterface::getSingleton()->uploadGeometry(meshSection);
	}
}

void Material::attachShader(ShaderSource* shader) {
	materialShader = RefCountedPtr<ShaderSource>(shader);
	passName = "MeshPass";
}

void MaterialInstance::attachTexture(const std::string& name) {
	TextureSource* tex = (TextureSource*)RenderInterface::getSingleton()->GetResourceByName(name, GPUResource::GResourceType::TEXTURE);
	TextureSource* cTex = TextureSource::copy(tex);
	textureIDs.push_back(RefCountedPtr<TextureSource>(cTex));

	if (!tex->loaded)
	{
		// update texture to GPU
		RenderInterface::getSingleton()->uploadTexture(tex);
	}
}