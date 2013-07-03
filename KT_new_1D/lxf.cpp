#include "lxf.h"

LxF::LxF()
{
    // 3 points method
    n_ = 3;
}

double LxF::get_flux(Cell *c)
{
    // speed of the information on the numerical space-time lattice
    double info_speed = c->dx()/c->dt();

    return 0.5*( c->cr->f - c->cl->f - info_speed*(c->cr->u + c->cl->u) );
}
