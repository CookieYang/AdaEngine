#pragma once
#include "MainLoop.h"
class SceneTree: public MainLoop {
public:
    virtual void Init();
    virtual void Run(double time);
    virtual void Destory();
};