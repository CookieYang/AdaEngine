#include "CameraComponent.h"
#include "SceneNode.h"

CameraComponent::CameraComponent(SceneNode* parent) :
	parent(parent),
	Zoom(ZOOM)
{
	trans = new TransformComponent;
}



glm::mat4 CameraComponent::GetViewMatrix()
{
	glm::mat4 localToWorld = parent->transComponent.GetTransform() * trans->GetTransform();
	glm::vec3 worldPosition = glm::vec3(localToWorld * glm::vec4(trans->GetPosition(), 1.0));
	glm::mat4 mat = glm::lookAt(worldPosition, worldPosition + GetCameraForward(localToWorld), GetCameraUP(localToWorld));
	return mat;
}

glm::mat4 CameraComponent::GetProjMatrix() {
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
	return glm::perspective(glm::radians(Zoom), 1280.0f / 720.0f, 0.1f, 100.0f);
}
