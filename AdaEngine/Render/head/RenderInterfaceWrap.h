#pragma once
#include "IRenderInterface.h"
#include "CommandQueue.h"
#include "RefCountedPtr.h"
#include <atomic>
#include <map>
#include "RenderPineline.h"
#include "CameraComponent.h"

class RenderInterfaceWrap;

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
	void renderingThreadDraw(double time);
	void renderingThreadFlush();
public:
	RenderInterfaceWrap(RenderInterface* innerRender, bool bCreateThread);
	~RenderInterfaceWrap();
	virtual void Init() override;
	virtual void sync() override;
	virtual void Draw(double time) override;
	virtual void Finish() override;

	RenderPineline* pineLine;
	CameraComponent* camera;

	virtual RenderPineline* createPineline(PinelineType type) override;
	virtual void addMaterialToPineline(Material* mat) override;
	virtual RenderPineline* getCurrentPineline() override;
	virtual CameraComponent* getActiveCamera() override;
	virtual void setActiveCamera(CameraComponent* camera) override;

	FUNC1(uploadTexture, TextureSource*)
	FUNC1(uploadGeometry, MeshSource*)
	FUNC2(resizeViewport, int, int)
	FUNC3(updateMaterialParam, MaterialInstance*, const std::string&, MaterialVar)

};