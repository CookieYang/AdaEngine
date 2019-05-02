#pragma once
#include "MainLoop.h"
#include <boost/shared_ptr.hpp>

class Application {
public:
	// do initilization(Engine)
	virtual void Initilize();
	// run
	virtual void Run();

	virtual void Destory();

	Application();

	virtual ~Application();

protected:
	boost::shared_ptr<MainLoop> mainLoop;
};