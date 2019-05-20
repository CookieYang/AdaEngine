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
	RenderInterface::getSingleton()->Init();
	doInit();
}

// CPU build render commands(vao, vbo...) to GPU
void Application::Run() {
	while (RenderInterface::getSingleton()->Valid()) {
		Engine::getInstance()->sceneTree->Run();
		doRun();
		RenderInterface::getSingleton()->sync();
		Engine::print("main Loop");
		RenderInterface::getSingleton()->Draw();
		RenderInterface::getSingleton()->SwapBuffer();
	}
	RenderInterface::getSingleton()->Finish();
	RenderInterface::getSingleton()->Destory();
}

void Application::Destory() {
	
}

void init_PyApplication(pybind11::module &m) {
	pybind11::class_<Application, PyApplication /* <--- trampoline*/>(m, "Application")
		.def(pybind11::init<>())
		.def("Initilize", &Application::Initilize)
		.def("Destory", &Application::Destory)
		.def("doRun", &Application::doRun)
		.def("doInit", &Application::doInit)
		.def("Run", &Application::Run);
};