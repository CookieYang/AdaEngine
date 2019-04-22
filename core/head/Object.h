#pragma once
#include <string>
#include "ClassDB.h"
class Object {
    DECLARE_CLASS(Object);
public:
    Object(){};
    virtual ~Object(){};
    static Object* CreatorObject(std::string className);
};