#include "IRenderInterface.h"
#include "Engine.h"

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

void RenderInterface::ClearCurrent() {
	Engine::getInstance()->win->ClearCurrent();
}

void RenderInterface::MakeCurrent() {
	Engine::getInstance()->win->MakeCurrent();
}