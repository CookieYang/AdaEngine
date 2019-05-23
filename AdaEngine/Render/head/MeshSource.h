#pragma once
#include "GPUResource.h"
#include "GeometryData.h"
#include <vector>

class MeshSource : public GPUResource {
public:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	std::vector<unsigned int> ebos;
	MeshSource() {};
	MeshSource(GeometryData* gData);
	~MeshSource();
	void setGeometry(GeometryData* gData);
private:
	RefCountedPtr<GeometryData> sections;
};