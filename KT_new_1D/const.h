#ifndef CONST_H
#define CONST_H

#include "function.h"

class Const : public Function
{
public:
    Const();

    virtual double evaluate(double x);
};

#endif // CONST_H
