#include "TextureSource.h"

TextureSource::TextureSource() {

}

void TextureSource::setImageRef(TextureData* imageData) {
	imageRef = RefCountedPtr<TextureData>(imageData);
}

TextureSource::~TextureSource() {

}