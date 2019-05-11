#include "GLContext.h"
#include <iostream>
GLContext::GLContext() {

}

GLContext::~GLContext() {
	clearContext();
}

bool GLContext::initContext() {
	if (!glfwInit())
		return false;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Ada Engine", NULL, NULL);

	if (!window)
	{
		clearContext();
		return false;
	}

	makeCurrent();

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		std::cout << glewGetErrorString(err) << std::endl;
		return false;
	}

	return true;
}

void GLContext::makeCurrent() {
	glfwMakeContextCurrent(window);
}

bool GLContext::isContextValid() {
	return !glfwWindowShouldClose(window);
}

void GLContext::swapBuffers() {
	glfwSwapBuffers(window);
}

void GLContext::clearContext() {
	glfwTerminate();
}

void GLContext::PollEvents() {
	glfwPollEvents();
}