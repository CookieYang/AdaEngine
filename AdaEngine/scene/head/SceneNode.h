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
	void setScale(DMath::vec_t s);
	void setRotatation(DMath::vec_t rot);
	void setPosition(DMath::vec_t pos);
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