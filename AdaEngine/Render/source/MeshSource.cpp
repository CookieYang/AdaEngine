#include "MeshSource.h"
void MeshSource::setGeometry(GeometryData* gData) {
	sections = RefCountedPtr<GeometryData>(gData);
}