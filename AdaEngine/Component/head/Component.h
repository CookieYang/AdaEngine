#pragma once
#include "RefCountedPtr.h"
class Component : public RefCountable{
public:
	Component() {};
	virtual ~Component() {};
};