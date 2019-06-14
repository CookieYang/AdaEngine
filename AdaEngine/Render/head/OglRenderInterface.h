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

	virtual void updateMaterialParam(MaterialInstance* mat, const std::string& paramName, MaterialVar var) override;

	virtual void uploadTexture(TextureSource* tex) override;

	virtual void uploadGeometry(MeshSource* mesh) override;

	virtual RenderPineline* createPineline(PinelineType type) override;
	virtual void _addMaterialToPineline(RenderInterfaceWrap* wrap, Material* mat) override;
	virtual void addMaterialToPineline(Material* mat) override {};
	virtual RenderPineline* getCurrentPineline() override { return nullptr; };
	virtual RenderPineline* _getCurrentPineline(RenderInterfaceWrap* wrap) override;

	virtual void resizeViewport(int width, int height) override;
	virtual void setActiveCamera(CameraComponent* camera) override {};
	virtual void _setActiveCamera(RenderInterfaceWrap* wrap, CameraComponent* camera) override;
	virtual CameraComponent* getActiveCamera() override { return nullptr; };
	virtual CameraComponent* _getActiveCamera(RenderInterfaceWrap* wrap) override;
private:
	std::unique_ptr<GLContext> context;
};