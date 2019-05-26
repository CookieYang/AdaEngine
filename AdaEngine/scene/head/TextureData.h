#pragma once
#include "CPUResource.h"
#include "FreeImage.h"

class TextureData : public CPUResource {
public:
	FIBITMAP* imageData;
	int width;
	int height;
	TextureData() {};
	~TextureData();
};