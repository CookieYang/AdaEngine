#pragma once
#include "Object.h"
class MainLoop: public Object {
	//DECLEAR_CLASS(MainLoop)
public:
    virtual bool Init();
    virtual void Run();
    virtual void Destory();
	MainLoop();
	virtual ~MainLoop();
};