#pragma once
#include "GPUResource.h"
#include "GeometryData.h"
#include <vector>
#include "Material.h"


struct MeshSection
{
	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;
	Material* material;
	MaterialInstance mInstance;
	GeometryData::VertexData* vData;
	volatile bool loaded = false;
};

class MeshSource : public GPUResource {
public:
	MeshSource():sectionNum(0) {};
	~MeshSource();
	void setGeometry(const std::string& name);
	MaterialInstance* getMatreialInstanceForSection(int sectionIndex);
	int getSectionNum();
	MeshSection* getMeshSection(int sectionIndex);
private:
	RefCountedPtr<GeometryData> sections;
	std::vector<MeshSection> meshSections;
	int sectionNum;
};