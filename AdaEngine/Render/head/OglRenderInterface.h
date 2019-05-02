#pragma once
#include "GLContext.h"
#include "IRenderInterface.h"
#include <boost/shared_ptr.hpp>
class OglRenderInterface : public RenderInterface {
public:
	virtual bool Init() override;
	virtual void Render() override;
	virtual void Destroy() override;
	OglRenderInterface() {};
	~OglRenderInterface();
private:
	boost::shared_ptr<GLContext> context;
};