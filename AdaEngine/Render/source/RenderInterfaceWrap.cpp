#include "RenderInterfaceWrap.h"
#include  "Engine.h"
#include "MeshSource.h"


void RenderInterfaceWrap::Init() {
	if (bRenderingThread) {
		renderingThread = new std::thread(std::bind(&RenderInterfaceWrap::renderingThreadCallback, this));
		while (!drawThreadUp)
		{
			Engine::sleep(10);
		}
	}
	else {
		innerRenderInterface->Init();
	}
}

void RenderInterfaceWrap::renderingThreadExit() {
	exit = true;
}

void RenderInterfaceWrap::renderingThreadDraw(double time) {
	if (!(--drawPending)) {
		innerRenderInterface->Draw(time);
	}
}

void RenderInterfaceWrap::renderingThreadFlush() {
	--drawPending;
}

void RenderInterfaceWrap::renderingThreadCallback() {
	renderingThreadLoop();
}

void RenderInterfaceWrap::renderingThreadLoop() {
	serverThreadID = std::this_thread::get_id();
	if (!drawThreadUp)
	{
		innerRenderInterface->Init();
	}
	exit = false;
	drawThreadUp = true;
	while (!exit) {
		cmdQueue.waitAndFlushOne();
	}
	cmdQueue.flushAll();
	innerRenderInterface->Finish();
}

void RenderInterfaceWrap::sync() {
	if (bRenderingThread) {
		++drawPending; // discard if the last frame  hasn't been draw
		cmdQueue.pushAndSync(this, &RenderInterfaceWrap::renderingThreadFlush);
	}
	else {
		cmdQueue.flushAll();
	}
}

void RenderInterfaceWrap::Draw(double time) {
	if (bRenderingThread) {
		++drawPending; 
		cmdQueue.push(this, &RenderInterfaceWrap::renderingThreadDraw, time);
	}
	else {
		innerRenderInterface->Draw(time);
	}
}

void RenderInterfaceWrap::Finish() {
	if (renderingThread)
	{
		cmdQueue.push(this, &RenderInterfaceWrap::renderingThreadExit);
		renderingThread->join();
		delete renderingThread;
		renderingThread = nullptr;
	}
	else {
		innerRenderInterface->Finish();
	}
	// free all rendering resource
}

RenderInterfaceWrap* RenderInterfaceWrap::wrap = nullptr;
RenderInterfaceWrap::RenderInterfaceWrap(RenderInterface* innerRender, bool bCreateThread):cmdQueue(bCreateThread) {
	wrap = this;
	innerRenderInterface = innerRender;
	bRenderingThread = bCreateThread;
	renderingThread = nullptr;
	drawPending = 0;
	drawThreadUp = false;
	exit = false;
	allocMutex = new std::mutex;
	poolMaxSize = INT_MAX;

	if (!bCreateThread) {
		serverThreadID = std::this_thread::get_id();
	}
	else {
		serverThreadID = std::thread::id();
	}
}

RenderInterfaceWrap::~RenderInterfaceWrap() {
	delete innerRenderInterface;
	delete allocMutex;
	delete pineLine;
}

RenderPineline* RenderInterfaceWrap::createPineline(PinelineType type) {
	if (std::this_thread::get_id() != serverThreadID) {
		cmdQueue.pushAndRet(innerRenderInterface, &RenderInterface::createPineline, type, &pineLine);
	}
	else {
		pineLine = innerRenderInterface->createPineline(type);
	}
	return pineLine;
}

RenderPineline* RenderInterfaceWrap::getCurrentPineline() {
	if (std::this_thread::get_id() != serverThreadID) {
		return pineLine;
	}
	else {
		RenderPineline* p;
		p = innerRenderInterface->_getCurrentPineline(this);
		return p;
	}
}

CameraComponent* RenderInterfaceWrap::getActiveCamera() {
	if (std::this_thread::get_id() != serverThreadID) {
		return camera;
	}
	else {
		CameraComponent* camera;
		camera = innerRenderInterface->_getActiveCamera(this);
		return camera;
	}
}

void RenderInterfaceWrap::setActiveCamera(CameraComponent* camera) {
	if (std::this_thread::get_id() != serverThreadID) {
		cmdQueue.push(innerRenderInterface, &RenderInterface::_setActiveCamera, this, camera);
	}
	else {
		innerRenderInterface->_setActiveCamera(this, camera);
	}
}

void RenderInterfaceWrap::addMaterialToPineline(Material* mat) {
	if (std::this_thread::get_id() != serverThreadID) {
		cmdQueue.push(innerRenderInterface, &RenderInterface::_addMaterialToPineline, this, mat);
	}
	else {
		innerRenderInterface->_addMaterialToPineline(this, mat);
	}
}
