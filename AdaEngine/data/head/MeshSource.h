#pragma once
#include "GPUResource.h"
#include "GeometryData.h"
#include <vector>
#include "Material.h"


struct MeshSection
{
	unsigned int passMask = 1;
	unsigned int vao = 0;
	std::vector<unsigned int> vbos;
	unsigned int ebo = 0;
	unsigned long drawCount = 0;
	RefCountedPtr<MaterialInstance> mInstance = nullptr;
	void attachMaterial(MaterialInstance* matInstance) {
		mInstance = RefCountedPtr<MaterialInstance>(matInstance);
		mInstance->mat->attachToMeshSection(this);
	}
};

class MeshSource : public GPUResource {
public:
	bool loaded;
	unsigned int passMask;
	MeshSource():sectionNum(0),passMask(1 << 1),loaded(false) {};
	~MeshSource();
	void setGeometry(const std::string& name);
	int getSectionNum();
	MeshSection* getMeshSection(int sectionIndex);
	GeometryData::VertexData* getSectionData(int sectionIndex);
private:
	RefCountedPtr<GeometryData> sections;
	std::vector<MeshSection*> meshSections;
	int sectionNum;
};