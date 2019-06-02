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
	//glm::mat4 mat = glm::lookAt(parent->transComponent.GetTransform() * Position, Position + Front, Up);
	//if (parent)
	//{
	//	return parent->transComponent.GetTransform() * mat;
	//}
	//else
	//{
	//	return mat;
	//}
	glm::mat4 e(1.0f);
	return e;
}

glm::mat4 CameraComponent::GetProjMatrix() {
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
	return glm::perspective(glm::radians(Zoom), 1280.0f / 720.0f, 0.1f, 100.0f);
}
