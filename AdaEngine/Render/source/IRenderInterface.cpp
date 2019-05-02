#include "IRenderInterface.h"
#include "OglRenderInterface.h"
boost::shared_ptr<RenderInterface> RenderInterface::CreateRenderInterface() {
	return boost::shared_ptr<RenderInterface>(new OglRenderInterface);
}