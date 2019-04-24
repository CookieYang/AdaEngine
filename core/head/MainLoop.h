#include "Object.h"
class MainLoop: public Object {
public:
    virtual void Init();
    virtual void Run(double time);
    virtual void Destory();
};