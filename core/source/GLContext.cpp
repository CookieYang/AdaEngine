#include "GLContext.h"
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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
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