#pragma once
#include <memory>

class MeshSource;
class Material;
class ShaderSource;
class TextureSource;
class GPUResource;

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

	virtual Material* createMaterial(std::string name) = 0;
	virtual ShaderSource* createShader(std::string name) = 0;
	virtual TextureSource* createTexture(std::string name) = 0;
	virtual MeshSource* createMesh(std::string name) = 0;
	virtual GPUResource* searchResourceByName(std::string name, GPUResource::GResourceType type) = 0;    // try to copy first

	RenderInterface();
	virtual ~RenderInterface();
	static RenderInterface* getSingleton();
private:
	static RenderInterface* singleton;
};