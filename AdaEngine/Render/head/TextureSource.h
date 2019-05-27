#pragma once
#include  "GPUResource.h"
#include "TextureData.h"

class TextureSource : public GPUResource {
	RefCountedPtr<TextureData> imageRef;
public:
	bool loaded;
	unsigned int textureID;
	std::string bindingName;
	void setImageRef(const std::string& name);
	int getWidth();
	int getHeight();
	unsigned char* getRawData();
	TextureSource();
	~TextureSource();
};