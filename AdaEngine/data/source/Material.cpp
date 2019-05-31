#include "Material.h"
#include "MeshSource.h"
#include "IRenderInterface.h"
void Material::attachToMeshSection(MeshSection* meshSection) {

	if (meshRefs.size() == 0) {
		// add to render pass once;
		
		RenderInterface::getSingleton()->addMaterialToPineline(this);
	}
	meshRefs.push_back(meshSection);
}

void Material::attachShader(ShaderSource* shader) {
	materialShader = RefCountedPtr<ShaderSource>(shader);
}

void MaterialInstance::attachTexture(const std::string& name) {
	TextureSource* tex = (TextureSource*)RenderInterface::getSingleton()->GetResourceByName(name, GPUResource::GResourceType::TEXTURE);
	MaterialVar var;
	var.mVar.tex = &tex->textureID;
	var.mType = MaterialVar::VarType::TEXTURE2D;
	materialVars["baseColor"] = var;
	textureRefs.push_back(RefCountedPtr<TextureSource>(tex));
	if (!tex->loaded)
	{
		// update texture to GPU
		RenderInterface::getSingleton()->uploadTexture(tex);
		tex->loaded = true;
	}
}

ShaderSource* Material::getShader() {
	return materialShader.get();
}

bool Material::getDirty() {
	return dirty;
}
void Material::setDirty(bool d) {
	dirty = d;
}