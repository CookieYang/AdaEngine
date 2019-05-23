#pragma once
#include "GPUResource.h"
#include "GeometryData.h"
#include <vector>
#include "Material.h"

class MeshSource : public GPUResource {
	struct MeshSection
	{
		unsigned int vao;
		unsigned int vbo;
		unsigned int ebo;
		RefCountedPtr<Material> material;
	};
public:
	MeshSource():sectionNum(0) {};
	~MeshSource();
	void setGeometry(GeometryData* gData);
	void setMaterial(Material* material, int index);
	int getSectionNum();
private:
	RefCountedPtr<GeometryData> sections;
	std::vector<MeshSection> meshSections;
	int sectionNum;
};