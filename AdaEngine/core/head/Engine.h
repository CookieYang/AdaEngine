#pragma once
#include "IRenderInterface.h"
class SceneTree;
class Engine {
public:
	static Engine* getInstance();
	void init();
	boost::shared_ptr<RenderInterface> renderInterface;
	boost::shared_ptr<SceneTree> sceneTree;
private:
	Engine() {};
	~Engine() {};
};