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

	std::map<std::string, RefCountedPtr<Material>> MaterialMap;
	std::map<std::string, RefCountedPtr<ShaderSource>> ShaderSourceMap;
	std::map<std::string, MeshSource*> MeshSourceMap;                         // 应当交给资源管理（导入时创建，目前就用名字吧）
	std::map<std::string, TextureSource*> TextureSourceMap;
	std::map<std::string, MaterialInstance*> MaterialInstanceMap;

	RenderPineline* pineLine;
	CameraComponent* camera;

	virtual Material* createMaterial(const std::string& name, const std::string& shaderName) override;
	virtual MaterialInstance* createMaterialInstance(const std::string& matInstanceName, const std::string& matName) override;

	virtual ShaderSource* createShader(const std::string& name) override;
	virtual TextureSource* createTexture(const std::string& name) override;
	virtual MeshSource* createMesh(const std::string& name) override;

	virtual RenderPineline* createPineline(PinelineType type) override;
	virtual void addMaterialToPineline(Material* mat) override;
	virtual RenderPineline* getCurrentPineline() override;
	virtual CameraComponent* getActiveCamera() override;
	virtual void setActiveCamera(CameraComponent* camera) override;

	FUNC1(uploadTexture, TextureSource*)
	FUNC1(uploadGeometry, MeshSource*)
	FUNC2(resizeViewport, int, int)
	FUNC3(updateMaterialParam, MaterialInstance*, const std::string&, MaterialVar)

	virtual GPUResource* GetResourceByName(std::string name, GPUResource::GResourceType type) override;
};