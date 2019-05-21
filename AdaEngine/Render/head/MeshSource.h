#pragma once
#include "RefCountedPtr.h"
#include "GeometryData.h"
#include <vector>

class MeshSource : public RefCountable {
public:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	std::vector<unsigned int> ebos;
	size_t resourceID;
private:
	RefCountedPtr<GeometryData> sections;
};