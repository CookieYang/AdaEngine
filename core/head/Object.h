#pragma once
#include <string>
#include "ClassDB.h"
class Object {
	DECLEAR_CLASS(Object);
public:
    Object(){};
    virtual ~Object(){};
    static Object* CreatorObject(std::string className);
};