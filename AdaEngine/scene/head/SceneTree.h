#pragma once
#include "MainLoop.h"
#include "IRenderInterface.h"
class SceneNode;

class SceneTree {
public:
    void Init();
    void Run();
    void Destory();
	void AddNode(boost::shared_ptr<SceneNode>& node);
	SceneTree() ;
	~SceneTree() ;
private:
	boost::shared_ptr<SceneNode> root;
};