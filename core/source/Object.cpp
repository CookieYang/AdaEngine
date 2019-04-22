#include "Object.h"
IMPLEMENT_CLASS(Object)

Object* Object::CreatorObject(std::string className)
{
    auto iter = ClassDB::m_classInfoMap.find(className);
    if (iter != ClassDB::m_classInfoMap.end()) {
        return iter->second->CreatorObject();
    }
    return nullptr;
}

bool Register(ClassInfo* classInfo) {
    if(classInfo) {
        if(ClassDB::m_classInfoMap.find(classInfo->m_className) == ClassDB::m_classInfoMap.end()) {
            ClassDB::m_classInfoMap.insert(std::map<std::string, ClassInfo*>::value_type(classInfo->m_className, classInfo));
        }
    }
}