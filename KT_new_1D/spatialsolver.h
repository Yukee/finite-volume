#ifndef SPATIALSOLVER_H
#define SPATIALSOLVER_H

#include "cell.h"
#include "copycell.h"

class SpatialSolver
{
protected:

    // the scheme is a n_ points method
    int n_;

public:
    SpatialSolver();

    // return numerical flux (such that (-1/dx)*flux = du/dt)
    virtual double get_flux(Cell * c) = 0;

    // return n_ (the number of points needed by the method)
    int get_n();

};

#endif // SPATIALSOLVER_H
