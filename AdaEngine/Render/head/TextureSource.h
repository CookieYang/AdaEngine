#pragma once
#include  "GPUResource.h"
#include "TextureData.h"

class TextureSource : public GPUResource {
private:
	RefCountedPtr<TextureData> imageRef;
public:
	void setImageRef(TextureData* imageData);
	TextureSource();
	~TextureSource();
};