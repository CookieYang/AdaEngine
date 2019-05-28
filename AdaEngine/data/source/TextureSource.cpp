#include "TextureSource.h"
#include "ResourceManager.h"

TextureSource::TextureSource(): loaded(false) {

}

void TextureSource::setImageRef(const std::string& name) {
	TextureData* texData = (TextureData*)ResourceManager::singleton()->GetResourceByName(name);
	imageRef = RefCountedPtr<TextureData>(texData);
}

int TextureSource::getWidth() {
	return imageRef->width;
}
int TextureSource::getHeight() {
	return imageRef->height;
}
unsigned char* TextureSource::getRawData() {
	return (unsigned char*)imageRef->imageData->data;
}

TextureSource::~TextureSource() {

}

