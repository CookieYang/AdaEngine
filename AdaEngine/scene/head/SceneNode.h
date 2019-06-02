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
	void Scale(DVector3<float> scale);
	void Rotate(DVector3<float> rotation);
	void Translate(DVector3<float> translate);
	virtual void ProcessEvent(Event* event);
	void Run();
	void updateTransform();
protected:
	std::vector<RefCountedPtr<SceneNode>> childrens;
	virtual void ProcessKeyEvent(Event* kEvent) {};
	virtual void ProcessMouseMoveEvent(Event* mEvent) {};
	virtual void ProcessScrollEvent(Event* sEvent) {};
	virtual void doRun() {};
	virtual void doUpdateTransform() {};
	SceneNode* weak_parent;                                           // be careful !!!
private:
	void AddChildren(SceneNode* child);
};