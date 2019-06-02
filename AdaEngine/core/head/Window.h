#pragma once
#include "Delegate.h"
#include "Event.h"

class GLFWwindow;
class Engine;

class Window {
	GLFWwindow* win;
public:
	Window();
	~Window();
	double GetCurrentTime();
	bool Init();
	bool Closed();
	void SwapBuffer();
	void SetSwapInterval(int i);
	void Teminal();
	void PollEvent();
	void MakeCurrent();
	void ClearCurrent();
	void setIcon(unsigned char* icon, int width, int height);
	static delegate<void(int, int)> resizeDelegate;
	static delegate<void(Event*)> keyDelegate;
	static delegate<void(MouseMoveEvent*)> moveDelegate;
	static delegate<void(ScrollEvent*)> scrollDelegate;
};