#pragma once
#include "GLContext.h"
#include "IRenderInterface.h"
#include <memory>
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
private:
	std::shared_ptr<GLContext> context;
	virtual void ClearContext() override;
	virtual void MakeCurrent() override;
};