#include "MainLoop.h"
#include "Engine.h"
#include "SceneTree.h"

MainLoop::MainLoop() {

}

void MainLoop::Init() {
	Engine::getInstance()->sceneTree->Init();
}

void MainLoop::Run(){
	Engine::getInstance()->sceneTree->Run();
}

void MainLoop::Destory() {
	Engine::getInstance()->sceneTree->Destory();
}

MainLoop::~MainLoop() {
	
}