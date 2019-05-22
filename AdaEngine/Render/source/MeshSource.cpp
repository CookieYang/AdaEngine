#include "MeshSource.h"
void MeshSource::setGeometry(GeometryData* gData) {
	sections = RefCountedPtr<GeometryData>(gData);
	size_t length = gData->sectionsData.size();
	vaos.resize(length, 0);
	vbos.resize(length, 0);
	ebos.resize(length, 0);
}