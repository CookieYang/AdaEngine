#pragma once
#include "Delegate.h"

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
	static delegate<void(int, int)> resizeDelegate;
};