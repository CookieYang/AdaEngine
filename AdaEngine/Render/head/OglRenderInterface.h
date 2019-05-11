#pragma once
#include "GLContext.h"
#include "IRenderInterface.h"
#include <memory>
class OglRenderInterface : public RenderInterface {
public:
	virtual bool Init() override;
	virtual void Render() override;
	virtual void Destroy() override;
	virtual bool Valid() override;
	OglRenderInterface() {};
	~OglRenderInterface();
private:
	std::shared_ptr<GLContext> context;
};