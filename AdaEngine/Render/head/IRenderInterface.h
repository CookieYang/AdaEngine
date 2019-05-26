#pragma once
#include <memory>
#include <string>
#include "RenderPineline.h"
#include "RenderPass.h"
#include "MeshSource.h"
#include "ShaderSource.h"
#include "TextureSource.h"

#define FUNC1(m_type, m_arg1)                          \
	virtual void m_type(m_arg1 p1) {						\
		if (std::this_thread::get_id() != serverThreadID) {                                                \
			cmdQueue.push(innerRenderInterface, &RenderInterface::m_type, p1);          \
		} else {                                                                                       \
			innerRenderInterface->m_type(p1);                                           \
		}                                                                                              \
	}

class RenderInterfaceWrap;

class RenderInterface {
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void SwapBuffer() = 0;
	virtual void ClearContext() = 0;
	virtual void MakeCurrent() = 0;
	virtual void Finish() = 0;             
	virtual void Destory() = 0;
	virtual bool Valid() = 0;
	virtual void sync() = 0;

	virtual Material* createMaterial(const std::string& name, const std::string& shaderName) = 0;
	virtual MaterialInstance* createMaterialInstance(const std::string& matInstanceName, const std::string& matName) = 0;
	virtual ShaderSource* createShader(const std::string& name) = 0;
	virtual TextureSource* createTexture(const std::string& name) = 0;
	virtual void uploadTexture(TextureSource* tex) = 0;
	virtual void uploadGeometry(MeshSection* mesh) = 0;
	virtual MeshSource* createMesh(const std::string& name) = 0;
	virtual GPUResource* GetResourceByName(std::string name, GPUResource::GResourceType type) = 0;
	virtual Material* _createMaterial(RenderInterfaceWrap* wrap, const std::string& name, const std::string& shaderName) { return nullptr; };
	virtual MaterialInstance* _createMaterialInstance(RenderInterfaceWrap* wrap, const std::string& matInstanceName, const std::string& matName) { return nullptr; };
	virtual void _addMaterialToPineline(RenderInterfaceWrap* wrap, Material* mat) { };
	virtual GPUResource* _GetResourceByName(RenderInterfaceWrap* wrap, std::string name, GPUResource::GResourceType type) { return nullptr; };

	virtual RenderPineline* createPineline(PinelineType type) = 0;
	virtual void addMaterialToPineline(Material* mat) = 0;
	virtual RenderPineline* getCurrentPineline() = 0;
	virtual RenderPineline* _getCurrentPineline(RenderInterfaceWrap* wrap) { return nullptr; };

	RenderInterface();
	virtual ~RenderInterface();
	static RenderInterface* getSingleton();
private:
	static RenderInterface* singleton;
};