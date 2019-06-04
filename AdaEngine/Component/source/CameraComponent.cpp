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
	DMath::matrix_t localToWorld = parent->transComponent.GetTransform() * trans->GetTransform();
	glm::vec3 forward = glm::vec3(localToWorld.v.dir.x, localToWorld.v.dir.y, localToWorld.v.dir.z);
	glm::vec3 up = glm::vec3(localToWorld.v.up.x, localToWorld.v.up.y, localToWorld.v.up.z);
	DMath::vec_t wPos = DMath::TransformPoint(trans->GetPosition(), localToWorld); 
	glm::vec3 worldPosition = glm::vec3(wPos.x, wPos.y, wPos.z);
	glm::mat4 mat = glm::lookAt(worldPosition, worldPosition + forward, up);
	return mat;
}

glm::mat4 CameraComponent::GetProjMatrix() {
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
	return glm::perspective(glm::radians(Zoom), 1280.0f / 720.0f, 0.1f, 100.0f);
}
