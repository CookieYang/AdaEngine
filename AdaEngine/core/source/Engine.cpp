#include "Engine.h"
#include <iostream>
#include "OglRenderInterface.h"
#include "RenderInterfaceWrap.h"
#include "ResourceManager.h"

Engine* Engine::getInstance() {
	static Engine engine;
	return &engine;
}

void Engine::init() {
	OglRenderInterface* oglRenderInterface = new OglRenderInterface;
	new RenderInterfaceWrap(oglRenderInterface, true);
	new ResourceManager;
	sceneTree = std::unique_ptr<SceneTree>(new SceneTree);
}

void Engine::sleep(double time) {
	std::chrono::milliseconds timespan((int)time); 
	std::this_thread::sleep_for(timespan);
}

void Engine::print(std::string log) {
	std::cout << log.c_str() << std::endl;
}
