#pragma once
#include "SceneTree.h"
#include "Window.h"
#include <string>
#include "pybind11.h"

class FIBITMAP;
class Event;

class Engine {
public:
	Engine() {};
	~Engine() {};
	static Engine* getInstance();
	void init();
	std::unique_ptr<SceneTree> sceneTree;
	std::unique_ptr<Window> win;
	static void sleep(double time);
	static void print(std::string log);
	static double getTime();
private:
	void resizeViewPort(int width, int height);
	void EventCallback(Event* event);
};

void init_Engine(pybind11::module& m);