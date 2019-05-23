#pragma once
#include "RawResource.h"
class CPUResource : public RawResource {
public:
	enum CResourceType
	{
		GEOMETRYDATA,
		SHADERDATA,
		IMAGEDATA
	};
	CResourceType resourceType;
};