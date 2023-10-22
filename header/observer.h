#ifndef H_OBSERVER
#define H_OBSERVER

#include "subject.h"
class Subject;
//neni hotove, protoze nechapu, proc musi byt observer mezi kamerou a shader programem
class Observer
{
public:
    virtual void notify(Subject* subject) = 0;
};

#endif // H_OBSERVER