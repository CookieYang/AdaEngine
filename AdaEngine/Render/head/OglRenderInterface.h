#pragma once
#include "GLContext.h"
#include "IRenderInterface.h"
#include <map>

class OglRenderInterface : public RenderInterface {
public:
	virtual void Init() override;
	virtual void Draw(double time) override;
	virtual void sync() override;
	virtual void Finish() override;
	OglRenderInterface();
	~OglRenderInterface();

	virtual Material* _createMaterial(RenderInterfaceWrap* wrap, const std::string& name, const std::string& shaderName) override;
	virtual Material* createMaterial(const std::string& name, const std::string& shaderName) override { return nullptr; };
	virtual MaterialInstance* createMaterialInstance(const std::string& matInstanceName, const std::string& matName) override { return nullptr; };
	virtual MaterialInstance* _createMaterialInstance(RenderInterfaceWrap* wrap, const std::string& matInstanceName, const std::string& matName) override;
	virtual void updateMaterialParam(MaterialInstance* mat, const std::string& paramName, MaterialVar var) override;


	virtual ShaderSource* createShader(const std::string& name) override;

	virtual TextureSource* createTexture(const std::string& name) override;
	virtual void uploadTexture(TextureSource* tex) override;

	virtual MeshSource* createMesh(const std::string& name) override;
	virtual void uploadGeometry(MeshSource* mesh) override;

	virtual RenderPineline* createPineline(PinelineType type) override;
	virtual void _addMaterialToPineline(RenderInterfaceWrap* wrap, Material* mat) override;
	virtual void addMaterialToPineline(Material* mat) override {};
	virtual RenderPineline* getCurrentPineline() override { return nullptr; };
	virtual RenderPineline* _getCurrentPineline(RenderInterfaceWrap* wrap) override;

	virtual GPUResource* _GetResourceByName(RenderInterfaceWrap* wrap, std::string name, GPUResource::GResourceType type) override;
	virtual GPUResource* GetResourceByName(std::string name, GPUResource::GResourceType type) override { return nullptr; };

	virtual void resizeViewport(int width, int height) override;
private:
	std::unique_ptr<GLContext> context;
};