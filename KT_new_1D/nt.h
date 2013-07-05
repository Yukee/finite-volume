#ifndef NT_H
#define NT_H

#include "spatialsolver.h"

/* Nessyahu and Tadmor scheme. This is a scheme based on a staggered time-space lattice.
 * ie the flux returned by the scheme after one timestep is the flux at a neighbouring cell interface
 * (see H. Nessyahu and E. Tadmor, J. Comput. Phys. 87, No 2., April 1990. (pp. 408-463)
 * or R. J. Leveque, Finite Volume Methods fot Hyperbolic Problems, Cambridge, 2002, pp. 198-200).
 * The numerical flux returned by the method get_flux of this class is the flux at the RIGHT neighbouring cell after 1 timestep. */

class NT : public SpatialSolver
{
public:
    NT();

    virtual double get_flux(Cell *c);
};

#endif // NT_H
