#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/quaternion.hpp"

struct DVector3
{
	float x;
	float y;
	float z;
	DVector3() :x(0), y(0), z(0) {};
	DVector3(float x, float y, float z) :x(x), y(y), z(y) {};
	glm::vec3 toVec3() { return glm::vec3(x, y, z); };
	DVector3(glm::vec3 vec3) { x = vec3.x; y = vec3.y; z = vec3.z; };
};

struct DVector2 {
	float x;
	float y;
	DVector2() :x(0), y(0) {};
	DVector2(float x, float y) :x(x), y(y) {};
	glm::vec2 toVec2() { return glm::vec2(x, y); };
	DVector2(glm::vec2 vec2) { x = vec2.x; y = vec2.y; };
};

// use for camera
glm::vec3 GetCameraForward(const glm::mat4& mat);

// use for normal
glm::vec3 GetForward(const glm::mat4& mat);

// use for camera
glm::vec3 GetCameraRight(const glm::mat4& mat);

// use for normal
glm::vec3 GetRight(const glm::mat4& mat);

// use for camera
glm::vec3 GetCameraUP(const glm::mat4& mat);

// use for normal
glm::vec3 GetUP(const glm::mat4& mat); 