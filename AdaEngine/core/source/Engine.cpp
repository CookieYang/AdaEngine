#include "Engine.h"
#include "SceneTree.h"
#include <iostream>

Engine* Engine::getInstance() {
	static Engine engine;
	return &engine;
}

void Engine::init() {
	renderInterface = RenderInterface::CreateRenderInterface();
	sceneTree = std::shared_ptr<SceneTree>(new SceneTree);
}
