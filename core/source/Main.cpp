#include "Main.h"
#include "SceneTree.h"
#include "Engine.h"

Main::Main() {
	mainLoop = new SceneTree;
}

Main::~Main() {
	Destory();
}

void Main::Initilize() {
	Engine::getInstance()->init();
	mainLoop->Init();
}

void Main::Run() {
	mainLoop->Run();
}

void Main::Destory() {
	delete mainLoop;
}