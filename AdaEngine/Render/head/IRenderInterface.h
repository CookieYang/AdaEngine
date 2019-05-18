#pragma once
#include <memory>
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
	RenderInterface();
	virtual ~RenderInterface();
	static RenderInterface* getSingleton();
private:
	static RenderInterface* singleton;
};