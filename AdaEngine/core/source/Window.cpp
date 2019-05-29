#include "Window.h"
#include "GLFW/glfw3.h"

delegate<void(int, int)> Window::resizeDelegate;

static void resizeCallback(GLFWwindow* win, int width, int height) {
	Window::resizeDelegate(width, height);
}

Window::Window() {
	
}

Window::~Window() {

}

bool Window::Init() {
	if (!glfwInit())
		return false;

	/* Create a windowed mode window and its OpenGL context */
	win = glfwCreateWindow(1280, 720, "Ada Engine", NULL, NULL);

	if (!win)
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // for mac

	glfwSetWindowSizeCallback(win, resizeCallback);
}

bool  Window::Closed() {
	return glfwWindowShouldClose(win);
}

double Window::GetCurrentTime() {
	return glfwGetTime();
}

void Window::SwapBuffer () {
	glfwSwapBuffers(win);
}

void Window::SetSwapInterval(int i) {
	glfwSwapInterval(i);
}

void Window::Teminal() {
	glfwTerminate();
}

void Window::PollEvent() {
	glfwPollEvents();
}

void Window::MakeCurrent() {
	glfwMakeContextCurrent(win);
}

void Window::ClearCurrent() {
	glfwMakeContextCurrent(nullptr);
}