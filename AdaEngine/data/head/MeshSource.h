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
	RefCountedPtr<MaterialInstance> mInstance;
	GeometryData::VertexData* vData;
	bool loaded = false;
	void resizeVBOs() {
		int size = 0;
		if (vData->vertexPosition.size() != 0)
		{
			size++;
		}
		if (vData->vertexUV.size() != 0) {
			size++;
		}
		if (vData->vertexNormal.size() != 0) {
			size++;
		}
		if (vData->vertexTangent.size() != 0) {
			size++;
		}
		if (vData->vertexBiTanget.size() != 0) {
			size++;
		}
		vbos.resize(size, 0);
	}
	void attachMaterial(MaterialInstance* matInstance) {
		mInstance = RefCountedPtr<MaterialInstance>(matInstance);
		mInstance->mat->attachToMeshSection(this);
	}
};

class MeshSource : public GPUResource {
public:
	unsigned int passMask;
	MeshSource():sectionNum(0),passMask(1) {};
	~MeshSource();
	void setGeometry(const std::string& name);
	int getSectionNum();
	MeshSection* getMeshSection(int sectionIndex);
private:
	RefCountedPtr<GeometryData> sections;
	std::vector<MeshSection> meshSections;
	int sectionNum;
};