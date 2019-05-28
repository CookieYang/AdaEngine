#include "TextureData.h"
#include "FreeImage.h"

TextureData::~TextureData() {
	FreeImage_Unload(imageData);
}