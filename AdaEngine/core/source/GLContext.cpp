#include "GLContext.h"
#include <iostream>

static void resizeCallback(GLFWwindow* win, int width, int height) {
	
}

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	glfwSetWindowSizeCallback(window, resizeCallback);

	makeCurrent();
	GLenum err = glewInit();
	makeCurrentNull();
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

void GLContext::makeCurrentNull() {
	glfwMakeContextCurrent(NULL);
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

double GLContext::getCurrentTime() {
	return glfwGetTime();
}