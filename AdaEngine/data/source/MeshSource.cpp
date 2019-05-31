#include "MeshSource.h"
#include "ResourceManager.h"
#include "IRenderInterface.h"

MeshSource::~MeshSource() {
	
}

int MeshSource::getSectionNum() {
	return sectionNum;
}

void MeshSource::setGeometry(const std::string& name) {
	// load CPU data
	GeometryData* gData = (GeometryData*)ResourceManager::singleton()->GetResourceByName(name);
	sectionNum = gData->sectionsData.size();
	sections = RefCountedPtr<GeometryData>(gData);
	for (size_t i = 0; i < sectionNum; i++)
	{
		MeshSection* section = new MeshSection;
		section->passMask = passMask;
		section->vbos.resize(gData->vboSize, 0);
		section->drawCount = gData->sectionsData[i].vertexIndices.size();
		meshSections.push_back(section);
	}
	if (!loaded) {
		// load to GPU
		RenderInterface::getSingleton()->uploadGeometry(this);
		loaded = true;
	}
	else {
		// TODO: change mesh
	}
}

void MeshSource::setTransform(const glm::mat4& trans) {
	for (auto section : meshSections) {
		section->trans = trans;
	}
}

MeshSection* MeshSource::getMeshSection(int sectionIndex) {
	return meshSections[sectionIndex];
}

GeometryData::VertexData* MeshSource::getSectionData(int sectionIndex) {
	return &sections.get()->sectionsData[sectionIndex];
}

