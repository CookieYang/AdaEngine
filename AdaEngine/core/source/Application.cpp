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

	ResourceManager::singleton()->loadTextureFromFile("defalut_tex_c", "resource/timg.jpg", FIF_JPEG, JPEG_DEFAULT);

	// create forward pineline
	RenderInterface::getSingleton()->createPineline(PinelineType::FORWARD);
	
	// create GPU resource
	ShaderSource* sha = RenderInterface::getSingleton()->createShader("defalut_shader");
	sha->setShaderData("defalut_shader_c");

	RenderInterface::getSingleton()->createMaterial("defalut_mat", "defalut_shader");

	MeshSource* mesh = RenderInterface::getSingleton()->createMesh("cube_mesh");
	mesh->setGeometry("cube_mesh_c");

	TextureSource* tex = RenderInterface::getSingleton()->createTexture("defalut_tex");
	tex->setImageRef("defalut_tex_c");

	MaterialInstance* matInstance = RenderInterface::getSingleton()->createMaterialInstance("defalut_mat_ins", "defalut_mat");
	matInstance->attachTexture("defalut_tex");
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
		Engine::getInstance()->sceneTree->Run();
		doRun();
		RenderInterface::getSingleton()->sync();
		RenderInterface::getSingleton()->Draw(currentTime);
		Engine::getInstance()->win->SwapBuffer();
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