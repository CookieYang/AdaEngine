#include "Application.h"
#include "SceneTree.h"
#include "Engine.h"
#include "ResourceManager.h"

Application::Application() {
	
}

Application::~Application() {
	Destory();
}

void Application::createDefalutResource() {

	// create forward pineline
	RenderInterface::getSingleton()->createPineline(PinelineType::FORWARD);
	
	// create  resource

	TextureSource* tex = ResourceManager::singleton()->createTexture("resource/asset/defalut_tex.json");

	ResourceManager::singleton()->createMaterial("resource/asset/defalut_mat.json");

	MeshSource* mesh = ResourceManager::singleton()->createMesh("resource/asset/cube_mesh.json");

	MaterialInstance* matInstance = ResourceManager::singleton()->createMaterialInstance("defalut_mat_ins", "defalut_mat");
	matInstance->loadDefalutValues();
}

void Application::Initilize() {
	Engine::getInstance()->init();
	Engine::getInstance()->sceneTree->Init();
	RenderInterface::getSingleton()->Init();
	createDefalutResource();
	doInit();
}

// CPU build render commands(vao, vbo...) to GPU
void Application::Run() {
	while (!Engine::getInstance()->win->Closed()) {
		double currentTime = Engine::getInstance()->win->GetCurrentTime();
		Engine::getInstance()->updateDeltaTime(currentTime);
		Engine::getInstance()->sceneTree->Run();
		doRun();
		RenderInterface::getSingleton()->sync();
		RenderInterface::getSingleton()->Draw(currentTime);
		Engine::getInstance()->win->PollEvent();
	}
	RenderInterface::getSingleton()->Finish();
	Engine::getInstance()->win->Teminal();
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