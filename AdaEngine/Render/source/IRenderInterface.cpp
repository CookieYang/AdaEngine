#include "IRenderInterface.h"
#include "OglRenderInterface.h"
RenderInterface* RenderInterface::singleton = nullptr;

RenderInterface* RenderInterface::getSingleton() {
	if (singleton) {
		return singleton;
	}
	return nullptr;
}

RenderInterface::RenderInterface() {
	singleton = this;
}

RenderInterface::~RenderInterface() {
	singleton = nullptr;
}