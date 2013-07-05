#ifndef KT2_H
#define KT2_H

#include "spatialsolver.h"

/* Second order accurate Kurganov and Tadmor scheme.
 * See A. Kurganov, E. Tadmor, New High-Res Central Schemes for Nonlinear Conservation Laws, J. Comput. Phys. 160, 241-282, 2000
 * */

class KT2 : public SpatialSolver
{
public:
    KT2();

    virtual double get_flux(Cell *c);
};

#endif // KT2_H
