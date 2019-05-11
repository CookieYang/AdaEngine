#pragma once
#include <memory>
class RenderInterface {
public:
	static std::shared_ptr<RenderInterface> CreateRenderInterface();
	virtual bool Init() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
	virtual bool Valid() = 0;
	virtual ~RenderInterface() {};
};