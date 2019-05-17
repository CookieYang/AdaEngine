#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"


class GLContext {
public:
	bool initContext();
	void makeCurrent();
	void makeCurrentNull();
	bool isContextValid();
	void swapBuffers();
	void clearContext();
	void PollEvents();
	GLContext();
	~GLContext();
private:
	GLFWwindow* window;
};