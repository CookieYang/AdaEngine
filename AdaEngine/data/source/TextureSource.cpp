#include "TextureSource.h"
#include "ResourceManager.h"
#include "Config.h"

TextureSource::TextureSource(): loaded(false) {

}

TextureSource::TextureSource(const std::string& jsonPath):loaded(false) {
	Config texConfig;
	texConfig.loadJson(jsonPath);
	this->setName(texConfig.asString("NAME"));
	this->setResPath(texConfig.asString("RESPATH"));
	this->setFormat(texConfig.asString("FORMAT"));
	TextureData* texData = ResourceManager::singleton()->loadTextureData(this->getResPath(), this->getFormat());
	imageRef = RefCountedPtr<TextureData>(texData);
}

void TextureSource::setImageRef(const std::string& name) {
	//TextureData* texData = (TextureData*)ResourceManager::singleton()->GetResourceByName(name);
	//imageRef = RefCountedPtr<TextureData>(texData);
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

