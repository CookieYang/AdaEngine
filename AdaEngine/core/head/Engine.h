#pragma once
#include "SceneTree.h"
#include "Window.h"
#include <string>

class FIBITMAP;
class Event;

class Engine {
public:
	static Engine* getInstance();
	void init();
	std::unique_ptr<SceneTree> sceneTree;
	std::unique_ptr<Window> win;
	static void sleep(double time);
	static void print(std::string log);
private:
	Engine() {};
	~Engine() {};
	void resizeViewPort(int width, int height);
	void EventCallback(Event* event);
};