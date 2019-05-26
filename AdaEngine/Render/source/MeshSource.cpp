#include "MeshSource.h"
#include "ResourceManager.h"

MeshSource::~MeshSource() {

}

int MeshSource::getSectionNum() {
	return sectionNum;
}

MaterialInstance* MeshSource::getMatreialInstanceForSection(int sectionIndex) {
	if (sectionIndex >= sectionNum) {
		return nullptr;
	}
	else {
		return &meshSections[sectionIndex].mInstance;
	}
}

void MeshSource::setGeometry(const std::string& name) {
	// load CPU data
	GeometryData* gData = (GeometryData*)ResourceManager::singleton()->GetResourceByName(name);
	sectionNum = gData->sectionsData.size();
	sections = RefCountedPtr<GeometryData>(gData);
	for (size_t i = 0; i < sectionNum; i++)
	{
		MeshSection section;
		section.vData = &gData->sectionsData[i];
		meshSections.push_back(section);
	}
}

MeshSection* MeshSource::getMeshSection(int sectionIndex) {
	return &meshSections[sectionIndex];
}

