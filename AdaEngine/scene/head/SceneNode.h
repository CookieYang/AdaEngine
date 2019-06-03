#pragma once
#include <vector>
#include <memory>
#include "TransformComponent.h"
#include "RefCountedPtr.h"
#include "Event.h"

class SceneNode: public RefCountable {
	friend class SceneTree;
public:
	TransformComponent transComponent;
	SceneNode(){};
	virtual ~SceneNode() {};
	void AttachToRoot();
	void AttachToParent(SceneNode* parent);
	void Scale(DVector3 scale);
	void Rotate(DVector3 rotation);
	void Translate(DVector3 translate);
	virtual bool ProcessEvent(Event* event);
	void Run();
	void updateTransform();
protected:
	std::vector<RefCountedPtr<SceneNode>> childrens;
	virtual bool ProcessKeyEvent(Event* kEvent) { return false; };
	virtual bool ProcessMouseMoveEvent(Event* mEvent) { return false; };
	virtual bool ProcessScrollEvent(Event* sEvent) { return false; };
	virtual void doRun() {};
	virtual void doUpdateTransform() {};
	SceneNode* weak_parent;                                           // be careful !!!
private:
	void AddChildren(SceneNode* child);
};