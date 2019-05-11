#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
class SceneNode {
public:
	SceneNode() {};
	virtual ~SceneNode() {};
	void AttachToParent(std::shared_ptr<SceneNode>& parent);
	void AttachToRoot();
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

	std::vector<std::shared_ptr<SceneNode>> childrens;
	std::weak_ptr<SceneNode> weak_parent;

private:
	void AddChildren(const std::shared_ptr<SceneNode>& child);
};