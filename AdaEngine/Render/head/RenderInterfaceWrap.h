#pragma once
#include "IRenderInterface.h"
#include "CommandQueue.h"
#include "RefCountedPtr.h"
#include <atomic>
#include <map>
#include "RenderPineline.h"

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

	std::map<std::string, RefCountedPtr<Material>> MaterialMap;
	std::map<std::string, RefCountedPtr<ShaderSource>> ShaderSourceMap;
	std::map<std::string, MeshSource*> MeshSourceMap;                         // 应当交给资源管理（导入时创建，目前就用名字吧）
	std::map<std::string, TextureSource*> TextureSourceMap;
	RenderPineline* pineLine;

	virtual Material* createMaterial(const std::string& name, const std::string& shaderName) override;
	virtual ShaderSource* createShader(const std::string& name) override;
	virtual TextureSource* createTexture(const std::string& name) override;
	virtual MeshSource* createMesh(const std::string& name) override;

	virtual RenderPineline* createPineline(PinelineType type) override;
	virtual void addMaterialToPineline(Material* mat) override;

	FUNC1(uploadTexture, TextureSource*)
	FUNC1(uploadGeometry, MeshSection*)
	FUNC1(passDraw, RenderPass*)

	virtual GPUResource* GetResourceByName(std::string name, GPUResource::GResourceType type) override;
};