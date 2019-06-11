#include "Window.h"
#include "GLFW/glfw3.h"

delegate<void(int, int)> Window::resizeDelegate;
delegate<void(Event*)> Window::keyDelegate;
delegate<void(MouseMoveEvent*)> Window::moveDelegate;
delegate<void(ScrollEvent*)> Window::scrollDelegate;
static bool bCursorEnable = true;
bool Window::bFirstMouse = true;
bool	Window::bSendEvent = false;
DMath::vec_t Window::lastMousePos = DMath::makeVect(0, 0);

static void resizeCallback(GLFWwindow* win, int width, int height) {
	Window::resizeDelegate(width, height);
}

static void keyCallback(GLFWwindow* win, int key, int scanCode, int action, int modBit) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		if (bCursorEnable)
		{
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			Window::bFirstMouse = true;
		}
		else {
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		bCursorEnable = !bCursorEnable;
		Window::bSendEvent = !Window::bSendEvent;
	}
	else {
		ACTION a = ACTION(action);
		KEY k = KEY(key);
		KeyEvent* event = new KeyEvent(k, a);
		Window::keyDelegate(event);
	}
}

static void mouseCallback(GLFWwindow* win, int key, int action, int modBit) {
	ACTION a = ACTION(action);
	KEY k = KEY(key);
	KeyEvent* event = new KeyEvent(k, a);
	Window::keyDelegate(event);
}

static void mousePosCallback(GLFWwindow* win, double xpos, double ypos) {
	DMath::vec_t pos = DMath::makeVect(xpos, ypos);
	if (Window::bFirstMouse)
	{
		Window::lastMousePos = pos;
		Window::bFirstMouse = false;
	}
	float xoffset = xpos - Window::lastMousePos.x;
	float yoffset = Window::lastMousePos.y - ypos;
	Window::lastMousePos = pos;
	MouseMoveEvent* mEvent = new MouseMoveEvent(xpos, ypos);
	mEvent->deltaX = xoffset;
	mEvent->deltaY = yoffset;
	Window::moveDelegate(mEvent);
}

static void scrollCallback(GLFWwindow* win, double xoffset, double yoffset) {
	Window::scrollDelegate(new ScrollEvent(xoffset, yoffset));
}

Window::Window():frame(DMath::makeVect(0, 0, 1024, 700)) {
	
}

Window::Window(DMath::vec_t frame):frame(frame) {

}

Window::~Window() {

}

bool Window::Init() {
	if (!glfwInit())
		return false;

	/* Create a windowed mode window and its OpenGL context */
	win = glfwCreateWindow(frame[2], frame[3], "Ada Engine", NULL, NULL);

	if (!win)
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // for mac

	glfwSetWindowSizeCallback(win, resizeCallback);
	glfwSetKeyCallback(win, keyCallback);
	glfwSetMouseButtonCallback(win, mouseCallback);
	glfwSetScrollCallback(win, scrollCallback);
	glfwSetCursorPosCallback(win, mousePosCallback);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	return true;
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

void Window::setIcon(unsigned char* icon, int width, int height) {
	GLFWimage* img = new GLFWimage;
	img->width = width;
	img->height = height;
	img->pixels = icon;
	glfwSetWindowIcon(win, 1, img);
}