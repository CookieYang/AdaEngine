#include "RenderInterfaceWrap.h"
#include  "Engine.h"

void RenderInterfaceWrap::Init() {
	if (bRenderingThread) {
		Engine::print("Creating rendering thread");
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

void RenderInterfaceWrap::renderingThreadDraw() {
	if (!(--drawPending)) {
		innerRenderInterface->Draw();
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
	//	innerRenderInterface->Draw();
		Engine::print("loop");
	}
	cmdQueue.flushAll();
	innerRenderInterface->Finish();
}

void RenderInterfaceWrap::sync() {
	if (bRenderingThread) {
		++drawPending; // keep pending while sync
		cmdQueue.pushAndSync(this, &RenderInterfaceWrap::renderingThreadFlush);
	}
	else {
		cmdQueue.flushAll();
	}
}

void RenderInterfaceWrap::Draw() {
	if (bRenderingThread) {
		++drawPending; 
		Engine::print("push draw call");
		cmdQueue.push(this, &RenderInterfaceWrap::renderingThreadDraw);
	}
	else {
		innerRenderInterface->Draw();
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

void RenderInterfaceWrap::Destory() {
	innerRenderInterface->Destory();
}

void RenderInterfaceWrap::SwapBuffer() {
	innerRenderInterface->SwapBuffer();
}

void RenderInterfaceWrap::ClearContext() {
	innerRenderInterface->ClearContext();
}

bool RenderInterfaceWrap::Valid() {
	return innerRenderInterface->Valid();
}

void RenderInterfaceWrap::MakeCurrent() {
	innerRenderInterface->MakeCurrent();
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
}