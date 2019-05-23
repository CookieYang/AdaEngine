#include "MeshSource.h"

MeshSource::~MeshSource() {

}

int MeshSource::getSectionNum() {
	return sectionNum;
}

void MeshSource::setGeometry(GeometryData* gData) {
	sections = RefCountedPtr<GeometryData>(gData);
	size_t length = gData->sectionsData.size();
	meshSections.resize(length);
	sectionNum = length;
}

void MeshSource::setMaterial(Material* material, int index) {
	meshSections[index].material = RefCountedPtr<Material>(material);
}
