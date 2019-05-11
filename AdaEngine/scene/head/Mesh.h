#pragma once
#include "SceneNode.h"
#include "GeometryData.h"
class Mesh : public SceneNode {
	//TODO
private:
	std::vector<std::shared_ptr<GeometryData>> meshDatas;
};