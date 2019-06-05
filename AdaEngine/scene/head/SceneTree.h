#pragma once
#include "IRenderInterface.h"
#include "RefCountedPtr.h"
class SceneNode;
class Event;
class SceneTree {
public:
    void Init();
    void Run();
    void Destory();
	void AddNode(SceneNode* node);
	void ProcessEvent(Event* event, bool bMouseEnable);
	SceneTree() ;
	~SceneTree() ;
private:
	RefCountedPtr<SceneNode> root;
};