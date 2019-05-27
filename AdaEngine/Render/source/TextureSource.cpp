#include "TextureSource.h"
#include "ResourceManager.h"

TextureSource::TextureSource(): loaded(false) {
	textureID = new unsigned int;
}

void TextureSource::setImageRef(const std::string& name) {
	TextureData* texData = (TextureData*)ResourceManager::singleton()->GetResourceByName(name);
	imageRef = RefCountedPtr<TextureData>(texData);
}

TextureSource* TextureSource::copy(TextureSource* tex) {
	TextureSource* texSource = new TextureSource;
	texSource->globalName = tex->globalName;
	texSource->textureID = tex->textureID;
	texSource->bindingName = "";
	texSource->imageRef = tex->imageRef;
	return texSource;
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

