#pragma once
#include "MainLoop.h"
#include "GLContext.h"

class SceneTree: public MainLoop {
	DECLEAR_CLASS(SceneTree)
public:
	SceneTree() ;
	~SceneTree() ;
    virtual bool Init();
    virtual void Run();
    virtual void Destory();
protected:
	GLContext* context;
};