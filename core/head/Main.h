#pragma once
#include "MainLoop.h"

class Main {
public:
	// do initilization(Engine)
	void Initilize();
	// run
	void Run();

	Main();

	~Main();

protected:
	MainLoop* mainLoop;

private:
	void Destory();
};