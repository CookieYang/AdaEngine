#pragma once
#include "SceneNode.h"
#include "RenderPass.h"

class SceneRenderable : public SceneNode {
public:
	SceneRenderable() {};
	virtual ~SceneRenderable() {};
	virtual void CreateRenderResource() {};
};

template <class Base = SceneRenderable>
class PySceneRenderable : public PySceneNode<Base> {
public:
	using PySceneNode<Base>::PySceneNode; 
	void CreateRenderResource() override { PYBIND11_OVERLOAD(void, Base, CreateRenderResource, ); }
};

void init_SceneRenderable(pybind11::module& m);