#pragma once
#include <memory>
class RenderInterface {
public:
	static std::shared_ptr<RenderInterface> CreateRenderInterface();
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void SwapBuffer() = 0;
	virtual void ClearContext() = 0;
	virtual void MakeCurrent() = 0;
	virtual void Destroy() = 0;
	virtual bool Valid() = 0;
	virtual ~RenderInterface() {};
};