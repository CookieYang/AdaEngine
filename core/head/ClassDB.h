#pragma once
#include <string>
#include <map>
class Object;
class ClassInfo;

typedef Object* (*ObjectConstructor)(void);
bool Register(ClassInfo* info);
class ClassInfo {
    public:
        ClassInfo(const std::string className, ObjectConstructor objConstructor):
        m_className(className),
        m_objConstructor(objConstructor) {
            Register(this);
        }
        Object* CreatorObject() const {
            return m_objConstructor ? (*m_objConstructor)() : nullptr;
        }
        ~ClassInfo(){}
    public:
        std::string m_className;
        ObjectConstructor m_objConstructor;
};

class ClassDB {
public:
    static std::map<std::string, ClassInfo*> m_classInfoMap;
}

#define DECLEAR_CLASS(name)\
protected:\
    static ClassInfo m_classInfo;\
public:\
    static Object* CreatorObject();

#define IMPLEMENT_CLASS(name)\
ClassInfo name::m_classInfo(#name, (ObjectConstructor)name::CreatorObject);\
Object* name::CreatorObject() {\
return new name;\
}
