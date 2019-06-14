#pragma once
#include "RefCountedPtr.h"
#include <string>
class RawResource: public RefCountable {
protected:
	std::string globalName;
	std::string resourcePath;
	std::string format;
public:
	void setFormat(const std::string& format);
	std::string getFormat();
	void setName(const std::string& name);
	std::string getName();
	void setResPath(const std::string& path);
	std::string getResPath();
	RawResource();
	virtual ~RawResource() {};
};