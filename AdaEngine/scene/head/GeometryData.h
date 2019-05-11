#pragma once
#include <glm/glm.hpp>
#include <vector>
class GeometryData {
public:
	struct VertexData
	{
		std::vector<glm::vec3> vertexPosition;
		std::vector<glm::vec2> vertexUV;
		std::vector<glm::vec3> vertexNormal;
		std::vector<glm::vec3> vertexTangent;
		std::vector<glm::vec3> vertexBTanget;
	};
	VertexData vertexData;
	void InitTestData();
};