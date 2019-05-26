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

	// create CPU data
	ResourceManager::singleton()->loadShaderGroupFromFile("defalut_shader_c");

	ResourceManager::singleton()->loadGeometryResourceFromFile("cube_mesh_c", "resource/Cube.OBJ");

	ResourceManager::singleton()->loadTextureFromFile("defalut_tex", "resource/defalut.jpg", FIF_JPEG, JPEG_ACCURATE);

	// create forward pineline
	RenderInterface::getSingleton()->createPineline(PinelineType::FORWARD);
	
	// create GPU resource
	ShaderSource* sha = RenderInterface::getSingleton()->createShader("defalut_shader");

	sha->setShaderData("defalut_shader_c");

	RenderInterface::getSingleton()->createMaterial("defalut_mat", "defalut_shader");

	RenderInterface::getSingleton()->createMesh("cube_mesh");

	RenderInterface::getSingleton()->createTexture("defalut_tex");
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