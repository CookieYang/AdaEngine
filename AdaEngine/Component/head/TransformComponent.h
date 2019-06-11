#pragma once
#include "AdaMath.h"
#include "Component.h"
class TransformComponent : public Component {
public:
	TransformComponent();
	DMath::matrix_t GetTransform();
	DMath::vec_t GetPosition();
	DMath::vec_t GetScale();
	DMath::vec_t GetRotation();
	void SetTransform(DMath::matrix_t newTransform);
	void setPosition(DMath::vec_t pos);
	void setScale(DMath::vec_t s);
	void setRotation(DMath::vec_t rot);
	void Translate(DMath::vec_t trans);
	void Scale(DMath::vec_t s);
	void Rotate(DMath::vec_t rot);
	void RotateAxis(float angle, DMath::vec_t axis);
private:
	DMath::matrix_t transform;
	DMath::vec_t position;
	DMath::vec_t scale;
	DMath::vec_t rotation;
};