#pragma once
#include <vector>
#include <memory>
#include "TransformComponent.h"
#include "RefCountedPtr.h"


class SceneNode: public RefCountable {
	friend class SceneTree;
public:
	TransformComponent transComponent;
	SceneNode(){};
	virtual ~SceneNode() {};
	void AttachToRoot();
	void AttachToParent(SceneNode* parent);
	void Scale(Vector3 scale);
	void Rotate(Vector3 rotation);
	void Translate(Vector3 translate);
	virtual void Run() {};
	virtual void updateTransform() {};
protected:
	std::vector<RefCountedPtr<SceneNode>> childrens;
	SceneNode* weak_parent;                                           // be careful !!!
private:
	void AddChildren(SceneNode* child);
};