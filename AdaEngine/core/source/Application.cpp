#include "Application.h"
#include "SceneTree.h"
#include "Engine.h"

Application::Application() {
	mainLoop= boost::shared_ptr<MainLoop>(new MainLoop);
}

Application::~Application() {
	Destory();
}

void Application::Initilize() {
	Engine::getInstance()->init();
	mainLoop->Init();
}

// CPU build render commands(vao, vbo...) to GPU
void Application::Run() {
	// CPU JOB
	mainLoop->Run();
	// GPU JOB
	Engine::getInstance()->renderInterface->Render();
}

void Application::Destory() {

}