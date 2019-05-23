#include "RawResource.h"

void RawResource::setName(const std::string& name) {
	globalName = name;
}

std::string RawResource::getName() {
	return globalName;
}

RawResource::RawResource() {
	globalName = "";
	resourcePath = "";
}