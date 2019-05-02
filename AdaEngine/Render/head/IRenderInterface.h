#pragma once
#include <boost/shared_ptr.hpp>
class RenderInterface {
public:
	static boost::shared_ptr<RenderInterface> CreateRenderInterface();
	virtual bool Init() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
	virtual ~RenderInterface() {};
};