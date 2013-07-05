#ifndef KT1_H
#define KT1_H

#include "spatialsolver.h"

/* First order accurate Kurganov and Tadmor scheme.
 * See A. Kurganov, E. Tadmor, New High-Res Central Schemes for Nonlinear Conservation Laws, J. Comput. Phys. 160, 241-282, 2000
 * */

class KT1 : public SpatialSolver
{
public:
    KT1();

    virtual double get_flux(Cell *c);
};

#endif // KT1_H
