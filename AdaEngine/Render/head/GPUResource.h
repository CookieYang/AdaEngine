#pragma once
#include "RawResource.h"

class GPUResource : public RawResource {
public:
	enum GResourceType
	{
		MESH,
		SHDADER,
		TEXTURE,
		MATRERIAL
	};
	GResourceType resourceType;
};