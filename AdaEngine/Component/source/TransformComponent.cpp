#include "TransformComponent.h"

TransformComponent::TransformComponent():
	transform(DMath::matrix_t()),
	rotation(DMath::makeVect(0.0, 0.0, 0.0)),
	scale(DMath::makeVect(1.0f, 1.0f, 1.0f)),
	position(DMath::makeVect(0.0f, 0.0f, 0.0f))
{
	DMath::composeMat(transform, position, scale, rotation);
}

DMath::matrix_t TransformComponent::GetTransform() {
	return transform;
}

DMath::vec_t TransformComponent::GetPosition() {
	return position;
}

DMath::vec_t TransformComponent::GetScale() {
	return scale;
}

DMath::vec_t TransformComponent::GetRotation() {
	return rotation;
}

void TransformComponent::SetTransform(DMath::matrix_t newTransform) {
	transform = newTransform;
	DMath::decomposeMat(DMath::matrix_t(transform), position, scale, rotation);
}

void TransformComponent::setPosition(DMath::vec_t pos) {
	position = pos;
	DMath::composeMat(transform, position, scale, rotation);
}

void TransformComponent::setScale(DMath::vec_t s) {
	scale = s;
	DMath::composeMat(transform, position, scale, rotation);
}

void TransformComponent::setRotation(DMath::vec_t rot) {
	rotation = rot;
	DMath::composeMat(transform, position, scale, rotation);
}

void TransformComponent::Rotate(DMath::vec_t rot){
	rotation += rot;
	DMath::composeMat(transform, position, scale, rotation);
}

void TransformComponent::Translate(DMath::vec_t trans) {
	position += trans;
	DMath::composeMat(transform, position, scale, rotation);
}

void TransformComponent::Scale(DMath::vec_t s) {
	scale += s;
	DMath::composeMat(transform, position, scale, rotation);
}

void TransformComponent::RotateAxis(float angle, DMath::vec_t axis) {

}