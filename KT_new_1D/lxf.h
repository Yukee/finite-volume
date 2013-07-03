#ifndef LXF_H
#define LXF_H

#include "spatialsolver.h"
#include "cell.h"
#include "copycell.h"

/* Lax-Friedrich scheme for the equation ut + f(u)x = 0 */

class LxF : public SpatialSolver
{

public:
    LxF();

    // LxF flux (such that (-1/dx)*flux = du/dt)
    virtual double get_flux(Cell *c);

};

#endif // LXF_H
