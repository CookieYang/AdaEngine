#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "RefCountedPtr.h"
enum SceneNodeType
{
	NODERENDERABLE,
	NODEDEFALUT
};

class SceneNode: public RefCountable {
public:
	SceneNode():type(SceneNodeType::NODEDEFALUT) {};
	virtual ~SceneNode() {};
	void AttachToParent(RefCountedPtr<SceneNode>& parent);
	void AttachToRoot();
	SceneNodeType getNodeType();
	inline glm::mat4 GetTransform();
	inline glm::vec3 GetPosition();
	inline glm::vec3 GetScale();
	inline glm::vec3 GetRotation();
	inline void SetTransform(glm::mat4 newTransform);
	inline void SetPosition(glm::vec3 newPosition);
	inline void SetScale(glm::vec3 newScale);
	inline void SetRotation(glm::vec3 newRotation);

protected:
	glm::mat4 transform;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	SceneNodeType type;
	std::vector<RefCountedPtr<SceneNode>> childrens;
	SceneNode* weak_parent;                                           // be careful !!!
private:
	void AddChildren(const RefCountedPtr<SceneNode>& child);
};