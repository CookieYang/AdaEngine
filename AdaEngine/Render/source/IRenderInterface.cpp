#include "IRenderInterface.h"
#include "OglRenderInterface.h"
std::shared_ptr<RenderInterface> RenderInterface::CreateRenderInterface() {
	return std::shared_ptr<RenderInterface>(new OglRenderInterface);
}