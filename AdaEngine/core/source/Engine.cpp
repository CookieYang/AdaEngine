#include "Engine.h"
#include <iostream>
#include "OglRenderInterface.h"
#include "RenderInterfaceWrap.h"
#include "ResourceManager.h"

void Engine::resizeViewPort(int width, int height) {
	RenderInterface::getSingleton()->resizeViewport(width, height);
}

void Engine::EventCallback(Event* event) {
	sceneTree->ProcessEvent(event, Window::bSendEvent);
}

double Engine::getTime() {
	return getInstance()->win->GetCurrentTime();
}


Engine* Engine::getInstance() {
	static Engine engine;
	return &engine;
}

void Engine::init() {
	config = std::unique_ptr<EngineConfig>(new EngineConfig);
	config->loadConfig();

	win = std::unique_ptr<Window>(new Window(config->windowFrame));
	win->Init();
	Window::resizeDelegate += mem_call(*Engine::getInstance(), &Engine::resizeViewPort);
	Window::keyDelegate += mem_call(*Engine::getInstance(), &Engine::EventCallback);
	Window::moveDelegate += mem_call(*Engine::getInstance(), &Engine::EventCallback);
	Window::scrollDelegate += mem_call(*Engine::getInstance(), &Engine::EventCallback);

	OglRenderInterface* oglRenderInterface = new OglRenderInterface;
	new RenderInterfaceWrap(oglRenderInterface, config->bUseRenderingThread);
	new ResourceManager;
	sceneTree = std::unique_ptr<SceneTree>(new SceneTree);

	// set icon
	FIBITMAP * img = FreeImage_Load(FIF_PNG, "resource/icon.png", PNG_DEFAULT);
	int Width = FreeImage_GetWidth(img);
	int Height = FreeImage_GetHeight(img);
	win->setIcon(FreeImage_GetBits(img), Width, Height);
	FreeImage_Unload(img);
}

void Engine::updateDeltaTime(double time) {
	deltaTime = time - lastTime;
	lastTime = time;
}

void Engine::sleep(double time) {
	std::chrono::milliseconds timespan((int)time); 
	std::this_thread::sleep_for(timespan);
}

void Engine::print(std::string log) {
	std::cout << log.c_str() << std::endl;
}

void init_Engine(pybind11::module& m) {
	pybind11::class_<Engine>(m, "Engine")
		.def_static("CurrrentTime", &Engine::getTime);
}
