#pragma once
#include <memory>
#include <string>
#include "RenderPineline.h"
#include "RenderPass.h"
#include "Material.h"

class TextureSource;
class MeshSource;

#define FUNC1(m_type, m_arg1)                          \
	virtual void m_type(m_arg1 p1) {						\
		if (std::this_thread::get_id() != serverThreadID) {                                                \
			cmdQueue.push(innerRenderInterface, &RenderInterface::m_type, p1);          \
		} else {                                                                                       \
			innerRenderInterface->m_type(p1);                                           \
		}                                                                                              \
	}

#define FUNC2(m_type, m_arg1, m_arg2)                          \
	virtual void m_type(m_arg1 p1, m_arg2 p2) {						\
		if (std::this_thread::get_id() != serverThreadID) {                                                \
			cmdQueue.push(innerRenderInterface, &RenderInterface::m_type, p1, p2);          \
		} else {                                                                                       \
			innerRenderInterface->m_type(p1, p2);                                           \
		}                                                                                              \
	}

#define FUNC3(m_type, m_arg1, m_arg2, m_arg3)                          \
	virtual void m_type(m_arg1 p1, m_arg2 p2, m_arg3 p3) {						\
		if (std::this_thread::get_id() != serverThreadID) {                                                \
			cmdQueue.push(innerRenderInterface, &RenderInterface::m_type, p1, p2, p3);          \
		} else {                                                                                       \
			innerRenderInterface->m_type(p1, p2, p3);                                           \
		}                                                                                              \
	}

class RenderInterfaceWrap;
class CameraComponent;

class RenderInterface {
public:
	virtual void Init() = 0;
	virtual void Draw(double time) = 0;
	virtual void ClearCurrent();
	virtual void MakeCurrent();
	virtual void Finish() = 0;             
	virtual void sync() = 0;

	virtual void updateMaterialParam(MaterialInstance* mat, const std::string& paramName, MaterialVar var) = 0;

	virtual void uploadTexture(TextureSource* tex) = 0;

	virtual void uploadGeometry(MeshSource* mesh) = 0;

	virtual void _addMaterialToPineline(RenderInterfaceWrap* wrap, Material* mat) { };

	virtual RenderPineline* createPineline(PinelineType type) = 0;
	virtual void addMaterialToPineline(Material* mat) = 0;
	virtual RenderPineline* getCurrentPineline() = 0;
	virtual RenderPineline* _getCurrentPineline(RenderInterfaceWrap* wrap) { return nullptr; };

	virtual void resizeViewport(int width, int height) = 0;
	virtual void setActiveCamera(CameraComponent* camera) = 0;
	virtual void _setActiveCamera(RenderInterfaceWrap* wrap, CameraComponent* camera) {};
	virtual CameraComponent* getActiveCamera() = 0;
	virtual CameraComponent* _getActiveCamera(RenderInterfaceWrap* wrap) { return nullptr; };

	RenderInterface();
	virtual ~RenderInterface();
	static RenderInterface* getSingleton();
private:
	static RenderInterface* singleton;
};