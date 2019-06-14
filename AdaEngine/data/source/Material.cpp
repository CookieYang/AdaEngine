#include "Material.h"
#include "MeshSource.h"
#include "IRenderInterface.h"
#include "ResourceManager.h"

std::pair<std::string, MaterialVar::VarType> pairArray[] =
{
	std::make_pair("MAT4",MaterialVar::MAT4),
	std::make_pair("TEXTURE2D",MaterialVar::TEXTURE2D)
};

std::map<std::string, MaterialVar::VarType> Material(pairArray, pairArray + sizeof(pairArray) / sizeof(pairArray[0]));

void Material::attachToMeshSection(MeshSection* meshSection) {

	if (meshRefs.size() == 0) {
		// add to render pass once;
		
		RenderInterface::getSingleton()->addMaterialToPineline(this);
	}
	meshRefs.push_back(meshSection);
}

Material::Material(ShaderSource* ss):dirty(true) {
	materialShader = RefCountedPtr<ShaderSource>(ss);
}

MaterialInstance::MaterialInstance() {

};

MaterialInstance::~MaterialInstance() {

}

void MaterialInstance::loadDefalutValues() {
	// load defalut textures;
	for (auto var : materialVars) {
		if (var.second.mType == MaterialVar::TEXTURE2D) {
			attachTexture(*var.second.mVar.texName);
			// free memory
			delete var.second.mVar.texName;
		}
	}
}

void MaterialInstance::attachTexture(const std::string& name) {
	TextureSource* tex = (TextureSource*)ResourceManager::singleton()->GetResourceByName(name, GPUResource::GResourceType::TEXTURE);
	if (tex)
	{
		materialVars["baseColor"].mVar.texID = &tex->textureID;
		textureRefs.push_back(RefCountedPtr<TextureSource>(tex));
		if (!tex->loaded)
		{
			// update texture to GPU
			RenderInterface::getSingleton()->uploadTexture(tex);
			tex->loaded = true;
		}
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