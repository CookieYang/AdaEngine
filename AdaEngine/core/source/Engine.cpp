#include "Engine.h"
#include <iostream>
#include "OglRenderInterface.h"
#include "RenderInterfaceWrap.h"
#include "ResourceManager.h"
#include <windows.h>


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
	Sleep(time);
}

void Engine::print(std::string log) {
	std::cout << log.c_str() << std::endl;
}
