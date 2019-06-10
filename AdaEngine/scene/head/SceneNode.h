#pragma once
#include <vector>
#include <memory>
#include "TransformComponent.h"
#include "RefCountedPtr.h"
#include "Event.h"
#include "pybind11.h"

class SceneNode: public RefCountable {
	friend class SceneTree;
public:
	TransformComponent transComponent;
	SceneNode(){};
	virtual ~SceneNode() {};
	void AttachToRoot();
	void AttachToParent(SceneNode* parent);
	void setScale(DMath::vec_t s);
	void setRotatation(DMath::vec_t rot);
	void setPosition(DMath::vec_t pos);
	void Run();
	void updateTransform();

	// expose to python
	virtual bool ProcessKeyEvent(Event* kEvent) { return false; };
	virtual bool ProcessMouseMoveEvent(Event* mEvent) { return false; };
	virtual bool ProcessScrollEvent(Event* sEvent) { return false; };
	virtual void doRun() {};
	virtual void doUpdateTransform() {};
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
	bool ProcessKeyEvent(Event* kEvent) override { PYBIND11_OVERLOAD(bool, Base, ProcessKeyEvent, kEvent); }
	bool ProcessMouseMoveEvent(Event* mEvent) override { PYBIND11_OVERLOAD(bool, Base, ProcessMouseMoveEvent, mEvent); }
	bool ProcessScrollEvent(Event* sEvent) override { PYBIND11_OVERLOAD(bool, Base, ProcessScrollEvent, sEvent); }
	void doRun() override { PYBIND11_OVERLOAD(void, Base, doRun, ); }
	void doUpdateTransform() override { PYBIND11_OVERLOAD(void, Base, doUpdateTransform, ); }
};

void init_SceneNode(pybind11::module& m);
