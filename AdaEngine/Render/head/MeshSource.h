#pragma once
#include "RefCountedPtr.h"
#include "GeometryData.h"
#include <vector>

class MeshSource : public RefCountable {
	 
private:
	std::vector<RefCountedPtr<GeometryData>> sections;
};