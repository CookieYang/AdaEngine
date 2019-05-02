#include "OglRenderInterface.h"

bool OglRenderInterface::Init() {
	context = boost::shared_ptr<GLContext>(new GLContext);
	return context->initContext();
}

void OglRenderInterface::Render() {
	while (context->isContextValid())
	{
		context->swapBuffers();
		context->PollEvents();
	}
}

void OglRenderInterface::Destroy() {
	context->clearContext();
}

OglRenderInterface::~OglRenderInterface() {
	Destroy();
}
