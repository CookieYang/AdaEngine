#pragma once
#include <glm/glm.hpp>
#include <boost/container/vector.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
class SceneNode {
public:
	SceneNode() {};
	virtual ~SceneNode() {};
	void AttachToParent(boost::shared_ptr<SceneNode>& parent);
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

	boost::container::vector<boost::shared_ptr<SceneNode>> childrens;
	boost::weak_ptr<SceneNode> weak_parent;

private:
	void AddChildren(const boost::shared_ptr<SceneNode>& child);
};