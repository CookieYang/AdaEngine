#pragma once
#include "SceneTree.h"
#include <string>

class Engine {
public:
	static Engine* getInstance();
	void init();
	std::unique_ptr<SceneTree> sceneTree;
	static void sleep(double time);
	static void print(std::string log);
private:
	Engine() {};
	~Engine() {};
};