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
	virtual void AttachToRoot();
	void AttachToParent(SceneNode* parent);
	inline glm::mat4 GetTransform();
	inline glm::vec3 GetPosition();
	inline glm::vec3 GetScale();
	inline glm::vec3 GetRotation();
	inline void SetTransform(glm::mat4 newTransform);
	inline void SetPosition(glm::vec3 newPosition);
	inline void SetScale(glm::vec3 newScale);
	inline void SetRotation(glm::vec3 newRotation);
	virtual void Run() {};
protected:
	glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	std::vector<RefCountedPtr<SceneNode>> childrens;
	SceneNode* weak_parent;                                           // be careful !!!
private:
	void AddChildren(SceneNode* child);
};