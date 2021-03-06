#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "CPUResource.h"
class GeometryData: public CPUResource {
public:
	struct VertexData
	{
		std::vector<glm::vec3> vertexPosition;
		std::vector<glm::vec2> vertexUV;
		std::vector<glm::vec3> vertexNormal;
		std::vector<glm::vec3> vertexTangent;
		std::vector<glm::vec3> vertexBiTanget;
		std::vector<unsigned int> vertexIndices;
	};
	std::vector<VertexData> sectionsData;
	unsigned int vboSize = 0;
};