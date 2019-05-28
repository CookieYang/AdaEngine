#include "GLContext.h"

GLContext::GLContext() {

}

GLContext::~GLContext() {
	
}

bool GLContext::initContext() {
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return false;
	}
	return true;
}