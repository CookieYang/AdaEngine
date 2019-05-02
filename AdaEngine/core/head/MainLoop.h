#pragma once
class MainLoop {

public:
    virtual void Init();
    virtual void Run();
    virtual void Destory();
	MainLoop();
	virtual ~MainLoop();
};