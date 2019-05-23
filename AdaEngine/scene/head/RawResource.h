#pragma once
#include "RefCountedPtr.h"
#include <string>
class RawResource: public RefCountable {
protected:
	std::string globalName;
	std::string resourcePath;
public:
	void setName(const std::string& name);
	std::string getName();
	RawResource();
	virtual ~RawResource() {};
};