#pragma once
#include "GLContext.h"
#include "IRenderInterface.h"
#include <map>

class OglRenderInterface : public RenderInterface {
public:
	virtual void Init() override;
	virtual void Draw() override;
	virtual void SwapBuffer() override;
	virtual void Destory() override;
	virtual bool Valid() override;
	virtual void sync() override;
	virtual void Finish() override;
	OglRenderInterface();
	~OglRenderInterface();

	virtual Material* _createMaterial(RenderInterfaceWrap* wrap, const std::string& name, const std::string& shaderName) override;
	virtual Material* createMaterial(const std::string& name, const std::string& shaderName) override { return nullptr; };
	virtual MaterialInstance* createMaterialInstance(const std::string& matInstanceName, const std::string& matName) override { return nullptr; };
	virtual MaterialInstance* _createMaterialInstance(RenderInterfaceWrap* wrap, const std::string& matInstanceName, const std::string& matName) override;
	virtual ShaderSource* createShader(const std::string& name) override;

	virtual TextureSource* createTexture(const std::string& name) override;
	virtual void uploadTexture(TextureSource* tex) override;

	virtual MeshSource* createMesh(const std::string& name) override;
	virtual void uploadGeometry(MeshSection* mesh) override;

	virtual RenderPineline* createPineline(PinelineType type) override;
	virtual void _addMaterialToPineline(RenderInterfaceWrap* wrap, Material* mat) override;
	virtual void addMaterialToPineline(Material* mat) override {};
	virtual RenderPineline* getCurrentPineline() override { return nullptr; };
	virtual RenderPineline* _getCurrentPineline(RenderInterfaceWrap* wrap) override;

	virtual GPUResource* _GetResourceByName(RenderInterfaceWrap* wrap, std::string name, GPUResource::GResourceType type) override;
	virtual GPUResource* GetResourceByName(std::string name, GPUResource::GResourceType type) override { return nullptr; };
private:
	std::shared_ptr<GLContext> context;
	virtual void ClearContext() override;
	virtual void MakeCurrent() override;
	double getCurrentTime();


};