#pragma once
#include "SceneNode.h"
#include "GeometryData.h"
class Mesh : public SceneNode {
	//TODO
private:
	boost::container::vector<boost::shared_ptr<GeometryData>> meshSections;
};