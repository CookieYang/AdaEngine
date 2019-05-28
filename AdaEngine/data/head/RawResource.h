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
	void setResPath(const std::string& path);
	std::string getResPath();
	RawResource();
	virtual ~RawResource() {};
};