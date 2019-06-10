#include "CameraComponent.h"
#include "SceneNode.h"
#include "IRenderInterface.h"

CameraComponent::CameraComponent(SceneNode* parent) :
	parent(parent),
	Zoom(ZOOM)
{
	trans = new TransformComponent;
}

void CameraComponent::setActive() {
	RenderInterface::getSingleton()->setActiveCamera(this);
}

glm::mat4 CameraComponent::GetViewMatrix()
{
	DMath::matrix_t localToWorld = parent->transComponent.GetTransform() * trans->GetTransform();
	//DMath::vec_t wPos = DMath::TransformPoint(trans->GetPosition(), localToWorld);
	//glm::vec3 worldPosition = glm::vec3(wPos.x, wPos.y, wPos.z);
	//glm::vec3 forward = glm::normalize(glm::vec3(localToWorld.m[0][2], localToWorld.m[1][2], localToWorld.m[2][2]));
	//glm::vec3 up = glm::normalize(glm::vec3(localToWorld.m[0][1], localToWorld.m[1][1], localToWorld.m[2][1]));
	//glm::mat4 mat = glm::lookAt(worldPosition, worldPosition + forward, up);
	glm::mat4 mat = glm::inverse(localToWorld.toGLM());
	return mat;
}

glm::mat4 CameraComponent::GetProjMatrix() {
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
	return glm::perspective(glm::radians(Zoom), 1280.0f / 720.0f, 0.01f, 200.0f);
}
