#include "TextureSource.h"

TextureSource::TextureSource(): loaded(false) {

}

void TextureSource::setImageRef(TextureData* imageData) {
	imageRef = RefCountedPtr<TextureData>(imageData);
}

TextureSource* TextureSource::copy(TextureSource* tex) {
	TextureSource* texSource = new TextureSource;
	texSource->globalName = tex->globalName;
	texSource->textureID = tex->textureID;
	texSource->bindingName = "";
	texSource->imageRef = tex->imageRef;
	return texSource;
}

TextureSource::~TextureSource() {

}

