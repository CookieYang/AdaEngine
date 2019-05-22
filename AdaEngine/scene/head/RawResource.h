#pragma once
#include "RefCountedPtr.h"
#include <string>
class RawResource: public RefCountable {
protected:
	std::string resourceName;
	std::string resourcePath;
};