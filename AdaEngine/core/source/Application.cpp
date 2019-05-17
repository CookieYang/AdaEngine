#include "Application.h"
#include "SceneTree.h"
#include "Engine.h"

Application::Application() {
	
}

Application::~Application() {
	Destory();
}

void Application::Initilize() {
	Engine::getInstance()->init();
	Engine::getInstance()->sceneTree->Init();
	Engine::getInstance()->renderInterface->Init();
}

// CPU build render commands(vao, vbo...) to GPU
void Application::Run() {
	while (Engine::getInstance()->renderInterface->Valid()) {
		Engine::getInstance()->sceneTree->Run();
		doRun();
		Engine::getInstance()->renderInterface->Draw();
		Engine::getInstance()->renderInterface->SwapBuffer();
	}
}

void Application::Destory() {
	
}

void init_PyApplication(pybind11::module &m) {
	pybind11::class_<Application, PyApplication /* <--- trampoline*/>(m, "Application")
		.def(pybind11::init<>())
		.def("Initilize", &Application::Initilize)
		.def("Destory", &Application::Destory)
		.def("doRun", &Application::doRun)
		.def("Run", &Application::Run);
};