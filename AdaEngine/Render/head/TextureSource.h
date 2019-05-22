#pragma once
#include "RefCountedPtr.h"
#include "TextureData.h"

class TextureSource : public RefCountable {
private:
	RefCountedPtr<TextureData> imageRef;
public:
	unsigned int bindingID;
	void setImageRef(TextureData* imageData);
	TextureSource();
	~TextureSource() {};
};