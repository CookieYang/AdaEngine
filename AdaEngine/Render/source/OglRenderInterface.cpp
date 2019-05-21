#include "OglRenderInterface.h"

void OglRenderInterface::Init() {
	// init gl in rendering thread
	MakeCurrent();
	glClearColor(0.3f, 0.1f, 0.2f, 1.0f);
}

void OglRenderInterface::SwapBuffer() {
	context->swapBuffers();
	context->PollEvents();
}

void OglRenderInterface::ClearContext() {
	context->makeCurrentNull();
}

void OglRenderInterface::MakeCurrent() {
	context->makeCurrent();
}

double OglRenderInterface::getCurrentTime() {
	return context->getCurrentTime();
}

void OglRenderInterface::Draw() {
	// rendering thread draw
	MakeCurrent();
	double time = getCurrentTime();
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(0, .5);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(-.5, -.5);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(.5, -.5);
	}
	glEnd();
	ClearContext();
}

bool OglRenderInterface::Valid() {
	return context->isContextValid();
}

void OglRenderInterface::sync() {

}

void OglRenderInterface::Finish() {

}

void OglRenderInterface::Destory() {
	context->clearContext();
}

OglRenderInterface::OglRenderInterface() {
	context = std::shared_ptr<GLContext>(new GLContext);
	context->initContext();
}

OglRenderInterface::~OglRenderInterface() {
	Destory();
}
