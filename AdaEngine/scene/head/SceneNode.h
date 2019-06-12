#pragma once
#include <vector>
#include <memory>
#include "TransformComponent.h"
#include "Event.h"
#include "Component.h"
#include "Bind.h"

class SceneNode: public RefCountable {
	friend class SceneTree;
public:
	TransformComponent transComponent;
	SceneNode(){};
	virtual ~SceneNode() {
		//components.clear();
		//childrens.clear();
	};
	void AttachToRoot();
	void AttachToParent(SceneNode* parent);
	void setScale(DMath::vec_t s);
	void setRotatation(DMath::vec_t rot);
	void setPosition(DMath::vec_t pos);
	void Run();
	void updateTransform();

	virtual void doRun() {};
	virtual void doUpdateTransform() {};
	std::vector<RefCountedPtr<Component>> components;
protected:
	std::vector<RefCountedPtr<SceneNode>> childrens;
	SceneNode* weak_parent;                                           // be careful !!!
private:
	virtual bool ProcessEvent(Event* event);
	void AddChildren(SceneNode* child);
};

template <class Base = SceneNode>
class PySceneNode : public Base {
public:
	using Base::Base; // Inherit constructors
	void doRun() override { PYBIND11_OVERLOAD(void, Base, doRun, ); }
	void doUpdateTransform() override { PYBIND11_OVERLOAD(void, Base, doUpdateTransform, ); }
};

void init_SceneNode(pybind11::module& m);
