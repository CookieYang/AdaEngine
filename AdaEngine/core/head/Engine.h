#pragma once
#include "IRenderInterface.h"
#include <string>
class SceneTree;
class Engine {
public:
	static Engine* getInstance();
	void init();
	RenderInterface* renderInterface;
	std::shared_ptr<SceneTree> sceneTree;
	static void sleep(double time);
	static void print(std::string log);
private:
	Engine() {};
	~Engine() {};
};