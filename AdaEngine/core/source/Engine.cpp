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
	bool bReadyRender = renderInterface->Init();
	if (!bReadyRender) {
		std::cout << "init Render Context failed" << std::endl;
	}
}
