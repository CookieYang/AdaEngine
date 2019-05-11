#pragma once
#include "IRenderInterface.h"
class SceneNode;

class SceneTree {
public:
    void Init();
    void Run();
    void Destory();
	void AddNode(std::shared_ptr<SceneNode>& node);
	SceneTree() ;
	~SceneTree() ;
private:
	std::shared_ptr<SceneNode> root;
};