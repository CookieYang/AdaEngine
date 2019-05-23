#include "TextureSource.h"

TextureSource::TextureSource(TextureData* imgData) {
	imageRef = RefCountedPtr<TextureData>(imgData);
}

TextureSource::TextureSource():bindingID(0) {

}

void TextureSource::setImageRef(TextureData* imageData) {
	
}

TextureSource::~TextureSource() {

}