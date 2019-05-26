#include "Material.h"
#include "MeshSource.h"
#include "IRenderInterface.h"
void Material::attachToMeshSection(MeshSection* meshSection) {

	if (!meshSection->loaded)
	{
		// upload mesh to GPU
		RenderInterface::getSingleton()->uploadGeometry(meshSection);
		meshSection->loaded = true;
	}

	if (meshRefs.size() == 0) {
		// add to render pass;
		RenderInterface::getSingleton()->addMaterialToPineline(this);
	}

	meshRefs.push_back(meshSection);
}

void Material::attachShader(ShaderSource* shader) {
	materialShader = RefCountedPtr<ShaderSource>(shader);
	passName = "MeshPass";
}

void MaterialInstance::attachTexture(const std::string& name) {
	TextureSource* tex = (TextureSource*)RenderInterface::getSingleton()->GetResourceByName(name, GPUResource::GResourceType::TEXTURE);
	TextureSource* cTex = TextureSource::copy(tex);
	cTex->bindingName = "baseColor";
	textureIDs.push_back(RefCountedPtr<TextureSource>(cTex));
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