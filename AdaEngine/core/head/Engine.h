#pragma once
#include "IRenderInterface.h"
class SceneTree;
class Engine {
public:
	static Engine* getInstance();
	void init();
	std::shared_ptr<RenderInterface> renderInterface;
	std::shared_ptr<SceneTree> sceneTree;
private:
	Engine() {};
	~Engine() {};
};