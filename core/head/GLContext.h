#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <memory>

class GLContext {
public:
	bool initContext();
	void makeCurrent();
	bool isContextValid();
	void swapBuffers();
	void clearContext();
	void PollEvents();
private:
	GLFWwindow* window;
};