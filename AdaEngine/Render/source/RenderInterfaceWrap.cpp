#include "RenderInterfaceWrap.h"
#include  "Engine.h"
#include "MeshSource.h"


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

void RenderInterfaceWrap::Draw() {
	if (bRenderingThread) {
		++drawPending; 
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

Material* RenderInterfaceWrap::createMaterial(const std::string& name, const std::string& shaderName) {
	if (std::this_thread::get_id() != serverThreadID) {
		Material* m = nullptr;
		allocMutex->lock();
		cmdQueue.pushAndRet(innerRenderInterface, &RenderInterface::_createMaterial, this, name, shaderName, &m);
		MaterialMap.insert(std::pair<std::string, RefCountedPtr<Material>>(m->getName(), RefCountedPtr<Material>(m)));
		allocMutex->unlock();
		return m;
	}
	else {
		Material* m = innerRenderInterface->_createMaterial(this, name, shaderName);
		MaterialMap.insert(std::pair<std::string, RefCountedPtr<Material>>(m->getName(), RefCountedPtr<Material>(m)));
		return m;
	}
}

MaterialInstance* RenderInterfaceWrap::createMaterialInstance(const std::string& matInstanceName, const std::string& matName) {
	if (std::this_thread::get_id() != serverThreadID) {
		MaterialInstance* m = nullptr;
		allocMutex->lock();
		cmdQueue.pushAndRet(innerRenderInterface, &RenderInterface::_createMaterialInstance, this, matInstanceName, matName, &m);
		MaterialInstanceMap.insert(std::pair<std::string, MaterialInstance*>(m->getName(), m));
		allocMutex->unlock();
		return m;
	}
	else {
		MaterialInstance* m = innerRenderInterface->_createMaterialInstance(this, matInstanceName, matName);
		MaterialInstanceMap.insert(std::pair<std::string, MaterialInstance*>(m->getName(), m));
		return m;
	}
}

ShaderSource* RenderInterfaceWrap::createShader(const std::string& name) {
	if (std::this_thread::get_id() != serverThreadID) {
		ShaderSource* m = nullptr;
		allocMutex->lock();
		cmdQueue.pushAndRet(innerRenderInterface, &RenderInterface::createShader, name, &m);
		ShaderSourceMap.insert(std::pair<std::string, RefCountedPtr<ShaderSource>>(m->getName(), RefCountedPtr<ShaderSource>(m)));
		allocMutex->unlock();
		return m;
	}
	else {
		ShaderSource* m = innerRenderInterface->createShader(name);
		ShaderSourceMap.insert(std::pair<std::string, RefCountedPtr<ShaderSource>>(m->getName(), RefCountedPtr<ShaderSource>(m)));
		return m;
	}
}

TextureSource* RenderInterfaceWrap::createTexture(const std::string& name) {
	if (std::this_thread::get_id() != serverThreadID) {
		TextureSource* m = nullptr;
		allocMutex->lock();
		cmdQueue.pushAndRet(innerRenderInterface, &RenderInterface::createTexture, name, &m);
		TextureSourceMap.insert(std::pair<std::string, TextureSource*>(m->getName(), m));
		allocMutex->unlock();
		return m;
	}
	else {
		TextureSource* m = innerRenderInterface->createTexture(name);
		TextureSourceMap.insert(std::pair<std::string, TextureSource*>(m->getName(), m));
		return m;
	}
}

MeshSource* RenderInterfaceWrap::createMesh(const std::string& name) {
	if (std::this_thread::get_id() != serverThreadID) {
		MeshSource* m = nullptr;
		allocMutex->lock();
		cmdQueue.pushAndRet(innerRenderInterface, &RenderInterface::createMesh, name, &m);
		MeshSourceMap.insert(std::pair<std::string, MeshSource*>(m->getName(), m));
		allocMutex->unlock();
		return m;
	}
	else {
		MeshSource* m = innerRenderInterface->createMesh(name);
		MeshSourceMap.insert(std::pair<std::string, MeshSource*>(m->getName(), m));
		return m;
	}
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

void RenderInterfaceWrap::addMaterialToPineline(Material* mat) {
	if (std::this_thread::get_id() != serverThreadID) {
		cmdQueue.push(innerRenderInterface, &RenderInterface::_addMaterialToPineline, this, mat);
	}
	else {
		innerRenderInterface->_addMaterialToPineline(this, mat);
	}
}

GPUResource* RenderInterfaceWrap::GetResourceByName(std::string name, GPUResource::GResourceType type) {
	if (std::this_thread::get_id() != serverThreadID) {
		GPUResource* res;
		allocMutex->lock();
		cmdQueue.pushAndRet(innerRenderInterface, &RenderInterface::_GetResourceByName, this, name, type, &res);
		allocMutex->unlock();
		return res;
	}
	else {
		GPUResource* res;
		 res = innerRenderInterface->_GetResourceByName(this, name, type);
		 return res;
	}
}