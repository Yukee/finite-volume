#ifndef Burgers_H
#define Burgers_H

#include "function.h"

class Burgers : public Function
{
public:
    Burgers();

    virtual double evaluate(double x);
};

#endif // Burgers_H
