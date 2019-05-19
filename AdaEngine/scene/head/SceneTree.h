#pragma once
#include "IRenderInterface.h"
#include "RefCountedPtr.h"
class SceneNode;

class SceneTree {
public:
    void Init();
    void Run();
    void Destory();
	void AddNode(RefCountedPtr<SceneNode>& node);
	SceneTree() ;
	~SceneTree() ;
private:
	RefCountedPtr<SceneNode> root;
};