#include "TextureSource.h"

TextureSource::TextureSource():bindingID(0) {

}

void TextureSource::setImageRef(TextureData* imageData) {
	imageRef = RefCountedPtr<TextureData>(imageData);
}