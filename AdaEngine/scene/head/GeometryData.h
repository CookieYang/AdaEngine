#pragma once
#include <glm/glm.hpp>
#include <boost/container/vector.hpp>
class GeometryData {
public:
	struct VertexData
	{
		boost::container::vector<glm::vec3> vertexPosition;
		boost::container::vector<glm::vec2> vertexUV;
		boost::container::vector<glm::vec3> vertexNormal;
		boost::container::vector<glm::vec3> vertexTangent;
		boost::container::vector<glm::vec3> vertexBTanget;
	};
	VertexData vertexData;
	void InitTestData();
};