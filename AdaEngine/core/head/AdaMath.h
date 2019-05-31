#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtc/quaternion.hpp"

struct Vector3
{
	float x;
	float y;
	float z;
	Vector3(float x, float y, float z) :x(x), y(y), z(y) {};
	glm::vec3 toVec3() { return glm::vec3(x, y, z); };
	Vector3(glm::vec3 vec3) { x = vec3.x; y = vec3.y; z = vec3.z; };
};