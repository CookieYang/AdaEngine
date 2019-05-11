#include "OglRenderInterface.h"

bool OglRenderInterface::Init() {
	context = std::shared_ptr<GLContext>(new GLContext);
	return context->initContext();
}

void OglRenderInterface::Render() {

	context->swapBuffers();
	context->PollEvents();
}

bool OglRenderInterface::Valid() {
	return context->isContextValid();
}

void OglRenderInterface::Destroy() {
	context->clearContext();
}

OglRenderInterface::~OglRenderInterface() {
	Destroy();
}
