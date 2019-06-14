#include "RawResource.h"

void RawResource::setName(const std::string& name) {
	globalName = name;
}

std::string RawResource::getName() {
	return globalName;
}

void RawResource::setFormat(const std::string& f) {
	format = f;
}

std::string RawResource::getFormat() {
	return format;
}

void RawResource::setResPath(const std::string& path) {
	resourcePath = path;
}

std::string RawResource::getResPath() {
	return resourcePath;
}

RawResource::RawResource() {
	globalName = "";
	resourcePath = "";
}