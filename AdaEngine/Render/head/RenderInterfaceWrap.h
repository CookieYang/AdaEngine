#pragma once
#include "IRenderInterface.h"
#include "CommandQueue.h"
#include <atomic>

class RenderInterfaceWrap : public RenderInterface {
	mutable RenderInterface* innerRenderInterface;
	mutable CommandQueue cmdQueue;
	static RenderInterfaceWrap* wrap;
	bool bRenderingThread;
	std::thread* renderingThread;
	std::atomic_ullong drawPending;
	volatile bool drawThreadUp;
	volatile bool exit;
	std::mutex* allocMutex;
	int poolMaxSize;
	std::thread::id serverThreadID;

	void renderingThreadCallback();
	void renderingThreadLoop();
	void renderingThreadExit();
	void renderingThreadDraw();
	void renderingThreadFlush();
public:
	RenderInterfaceWrap(RenderInterface* innerRender, bool bCreateThread);
	~RenderInterfaceWrap();
	virtual void Init() override;
	virtual void sync() override;
	virtual void Draw() override;
	virtual void Finish() override;
	virtual void Destory() override;
	virtual void SwapBuffer() override;
	virtual void ClearContext() override;
	virtual void MakeCurrent() override;
	virtual bool Valid() override;
};