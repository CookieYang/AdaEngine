#include "AdaMath.h"

glm::vec3 GetCameraForward(const glm::mat4& mat) {
	return glm::vec3(mat[0][2], mat[1][2], mat[2][2]);
}

// use for normal
glm::vec3 GetForward(const glm::mat4& mat) {
	return glm::vec3(mat[2][0], mat[2][1], mat[2][2]);
}

// use for camera
glm::vec3 GetCameraRight(const glm::mat4& mat) {
	return glm::vec3(mat[0][0], mat[1][0], mat[2][0]);
}

// use for normal
glm::vec3 GetRight(const glm::mat4& mat) {
	return glm::vec3(mat[0][0], mat[0][1], mat[0][2]);
}

// use for camera
glm::vec3 GetCameraUP(const glm::mat4& mat) {
	return glm::vec3(mat[0][1], mat[1][1], mat[2][1]);
}

// use for normal
glm::vec3 GetUP(const glm::mat4& mat) {
	return glm::vec3(mat[1][0], mat[1][1], mat[1][2]);
}