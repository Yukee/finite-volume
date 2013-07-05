#ifndef LIN_H
#define LIN_H

#include "function.h"

class Lin : public Function
{
public:
    Lin();

    virtual double evaluate(double x);
};

#endif // LIN_H
