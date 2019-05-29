#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "RefCountedPtr.h"

class SceneNode: public RefCountable {
	friend class SceneTree;
public:
	SceneNode(){};
	virtual ~SceneNode() {};
	void AttachToRoot();
	void AttachToParent(SceneNode* parent);
	glm::mat4 GetTransform();
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();
	void SetTransform(glm::mat4 newTransform);
	void SetPosition(glm::vec3 newPosition);
	void SetScale(glm::vec3 newScale);
	void SetRotation(glm::vec3 newRotation);
	virtual void Run() {};
protected:
	virtual void updateTransform(const glm::mat4& tran);
	glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	std::vector<RefCountedPtr<SceneNode>> childrens;
	SceneNode* weak_parent;                                           // be careful !!!
private:
	void AddChildren(SceneNode* child);
};