#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/quaternion.hpp"

template <class T>
struct DVector3
{
	T x;
	T y;
	T z;
	DVector3(float x, float y, float z) :x(x), y(y), z(y) {};
	glm::vec3 toVec3() { return glm::vec3(x, y, z); };
	DVector3(glm::vec3 vec3) { x = vec3.x; y = vec3.y; z = vec3.z; };
};

template <class T>
struct DVector2 {
	T x;
	T y;
	DVector2(T x, T y) :x(x), y(y) {};
	glm::vec2 toVec2() { return glm::vec2(x, y); };
	DVector2(glm::vec2 vec2) { x = vec2.x; y = vec2.y; };
};