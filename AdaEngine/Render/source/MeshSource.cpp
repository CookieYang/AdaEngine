#include "MeshSource.h"
MeshSource::MeshSource(GeometryData* gData) {
	sections = RefCountedPtr<GeometryData>(gData);
	size_t length = gData->sectionsData.size();
	vaos.resize(length, 0);
	vbos.resize(length, 0);
	ebos.resize(length, 0);
	// upload to gpu (sync)
}

MeshSource::~MeshSource() {

}

void MeshSource::setGeometry(GeometryData* gData) {

}
