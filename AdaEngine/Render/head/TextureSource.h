#pragma once
#include  "GPUResource.h"
#include "TextureData.h"

class TextureSource : public GPUResource {
private:
	RefCountedPtr<TextureData> imageRef;
public:
	volatile bool loaded;
	unsigned int textureID;
	std::string bindingName;
	static TextureSource* copy(TextureSource* tex);
	void setImageRef(TextureData* imageData);
	TextureSource();
	~TextureSource();
};